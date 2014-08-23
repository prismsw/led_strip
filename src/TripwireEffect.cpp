#include "TripwireEffect.h"
#include "Pins.h"
#include "Timer.h"

#include <Arduino.h>


TripwireEffect::TripwireEffect(const Color& color, int treshold, int interval):Effect(color) {
    this->onColor = new Color(color);
    this->black = new Color(0,0,0);

    this->interval = interval;
    this->usTimer = new Timer(interval);
    this->tripwire = new USTripwire(0, treshold, 200);
}

TripwireEffect::~TripwireEffect() {
    delete onColor;
    delete black;

    delete usTimer;
    delete tripwire;
}

void TripwireEffect::update() {
    if(usTimer->tick()) {
        tripwire->update();

        if(tripwire->getCount() > 0) {
            *currentColor = *onColor;
        }
        else {
            *currentColor = *black;
        }
    }
}

void TripwireEffect::setSpeed(double speed) {
    return;
}

unsigned char TripwireEffect::id() {
    return 6;
}
