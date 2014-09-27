#include "USTripwire.h"
#include "Pins.h"
#include "Timer.h"

#include <Arduino.h>

USTripwire::USTripwire(unsigned int holdTime, byte inCount, byte treshold, byte maxDist) {
    this->treshold = 120;
    this->inCount = inCount;
    this->usLeft = new NewPing(US1_TRIGGER_PIN, US1_ECHO_PIN, maxDist);
    this->usRight = new NewPing(US2_TRIGGER_PIN, US2_ECHO_PIN, maxDist);
    this->holdTimer = new Timer(holdTime);
}

USTripwire::~USTripwire() {
    delete usLeft;
    delete usRight;
}

byte USTripwire::getCount() const {
    return inCount;
}

SensorState USTripwire::getState() const {
    return state;
}

Event USTripwire::update() {
    SensorEvent ser = processRight();
    Event e1 = processStateMachine(ser);
    processEvent(e1);

    SensorEvent sel = processLeft();
    Event e2 = processStateMachine(sel);
    processEvent(e2);

    if(holdTimer->tick()) {
        processStateMachine(HOLD_OUT);
    }

    // TODO actually return something
    return NOTHING;
}

void USTripwire::processEvent(Event e) {
    if(e == ENTERED) {
        inCount++;
    }
    else if(e == EXITED) {
        if(inCount > 0) {
            inCount--;
        }
    }
}

SensorEvent USTripwire::processLeft() {
    byte dist = usLeft->convert_cm(usLeft->ping_median(3));

    // Left is tripped
    if(state == R_L || state == C_L || state == L_C || state == L_R) {
        if(dist < treshold) {
            return NONE;
        }
        else {
            return L_OUT;
        }
    }
    else {
        if(dist < treshold) {
            return L_IN;
        }
        else {
            return NONE;
        }
    }
}

SensorEvent USTripwire::processRight() {
    byte dist = usRight->convert_cm(usRight->ping_median(3));

    // Right is tripped
    if(state == R_L || state == C_R || state == R_C || state == L_R) {
        if(dist < treshold) {
            return NONE;
        }
        else {
            return R_OUT;
        }
    }
    else {
        if(dist < treshold) {
            return R_IN;
        }
        else {
            return NONE;
        }
    }
}

Event USTripwire::processStateMachine(SensorEvent e) {
    Event retEvent = NOTHING;

    switch(state) {
        case C_C:
            switch(e) {
                case R_IN:
                    state = R_C;
                    break;
                case L_IN:
                    state = L_C;
                    break;
            }
            break;
        case R_C:
            switch(e) {
                case L_IN:
                    state = R_L;
                    break;
                case R_OUT:
                    state = H_R_C;
                    holdTimer->reset();
                    break;
            }
            break;
        case H_R_C:
            switch(e) {
                case L_IN:
                    state = R_L;
                    break;
                case R_IN:
                    state = R_C;
                    break;
                case HOLD_OUT:
                    state = C_C;
                    break;
            }
            break;
        case R_L:
            switch(e) {
                case R_OUT:
                    state = C_L;
                    break;
                case L_OUT:
                    state = R_C;
                    break;
            }
            break;
        case C_L:
            switch(e) {
                case L_OUT:
                    state = C_C;
                    retEvent = ENTERED;
                    break;
                case R_IN:
                    state = R_L;
                    break;
            }
            break;
        case L_C:
            switch(e) {
                case R_IN:
                    state = L_R;
                    break;
                case L_OUT:
                    state = H_L_C;
                    holdTimer->reset();
                    break;
            }
            break;
        case H_L_C:
            switch(e) {
                case R_IN:
                    state = L_R;
                    break;
                case L_IN:
                    state = L_C;
                    break;
                case HOLD_OUT:
                    state = C_C;
                    break;
            }
            break;
        case L_R:
            switch(e) {
                case L_OUT:
                    state = C_R;
                    break;
                case R_OUT:
                    state = L_C;
                    break;
            }
            break;
        case C_R:
            switch(e) {
                case R_OUT:
                    state = C_C;
                    retEvent = EXITED;
                    break;
                case L_IN:
                    state = L_R;
                    break;
            }
            break;
    }

    return retEvent;
}
