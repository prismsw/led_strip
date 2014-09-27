#ifndef US_TRIPWIRE_H
#define US_TRIPWIRE_H

#include "Timer.h"

#include <Arduino.h>
#include <NewPing.h>

/**
 * SensorState - holds the current sensor state for our state machine
 * Format: [HOLD]_First_Second
 * R: Right
 * L: Left
 * C: Clear
 * A H indicates a hold state, meaning it will reset after a time
 */
enum SensorState {
    C_C,
    R_C,
    H_R_C,
    R_L,
    C_L,
    H_L_C,
    L_C,
    L_R,
    C_R
};

enum SensorEvent {
    NONE,
    R_IN,
    R_OUT,
    L_IN,
    L_OUT,
    HOLD_OUT
};

enum Event {
    NOTHING,
    ENTERED,
    EXITED
};

class USTripwire {
    private:
        NewPing *usLeft;
        NewPing *usRight;
        byte treshold;

        SensorState state = C_C;
        byte inCount;

        void processEvent(Event e);
        SensorEvent processLeft();
        SensorEvent processRight();
        
        Event processStateMachine(SensorEvent e);
        Timer *holdTimer;
    public:
        USTripwire(unsigned int holdTime=5000, byte inCount=0, byte treshold=120, byte maxDist=200);
        ~USTripwire();

        byte getCount() const;
        SensorState getState() const;

        Event update();
};

#endif
