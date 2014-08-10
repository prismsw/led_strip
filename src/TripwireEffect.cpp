#include "TripwireEffect.h"
#include "Pins.h"
#include "Timer.h"

#include <Arduino.h>

TripwireEffect::TripwireEffect(int treshold, int interval, int lockTime) {
    this->treshold = treshold;
    this->interval = interval;
    this->lockTime = lockTime;
    this->sonar = new NewPing(US1_TRIGGER_PIN, US1_ECHO_PIN, 200);
    this->usTimer = new Timer(interval);
}

TripwireEffect::~TripwireEffect() {
    delete sonar;
    delete usTimer;
}

void TripwireEffect::nextColor(Color* current) {
    if(usTimer->tick()) {
        if((millis() - lastTripped) > lockTime) {
            unsigned int distance = sonar->convert_cm(sonar->ping_median(3));
            Serial.println(distance);

            if(distance > 0 && distance < treshold) {
                lastTripped = millis();
                if(!isTripped) {
                    isTripped = true;

                    if(current->getR() == 0) {
                        current->setRGB(255,255,255);
                    }
                    else {
                        current->setRGB(0,0,0);
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
