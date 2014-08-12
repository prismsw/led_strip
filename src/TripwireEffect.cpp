#include "TripwireEffect.h"
#include "Pins.h"
#include "Timer.h"

#include <Arduino.h>

TripwireEffect::TripwireEffect(Color color, int treshold, int interval, int lockTime):Effect(color) {
    this->onColor = new Color(color);
    this->black = new Color(0,0,0);

    this->treshold = treshold;
    this->interval = interval;
    this->lockTime = lockTime;
    this->sonar = new NewPing(US1_TRIGGER_PIN, US1_ECHO_PIN, 200);
    this->usTimer = new Timer(interval);
}

TripwireEffect::~TripwireEffect() {
    delete onColor;
    delete black;

    delete sonar;
    delete usTimer;
}

void TripwireEffect::update() {
    if(usTimer->tick()) {
        if((millis() - lastTripped) > lockTime) {
            unsigned int distance = sonar->convert_cm(sonar->ping_median(3));

            if(distance > 0 && distance < treshold) {
                lastTripped = millis();
                if(!isTripped) {
                    isTripped = true;

                    if(*currentColor == *black) {
                        *currentColor = *onColor;
                    }
                    else {
                        *currentColor = *black;
                    }
                }
            }
            else {
                isTripped = false;
            }
        }
    }
}

void TripwireEffect::setSpeed(double speed) {
    return;
}

unsigned char TripwireEffect::id() {
    return 6;
}
