#include "TimedEffect.h"
#include <Arduino.h>

TimedEffect::TimedEffect(int interval) {
    this->timer = new Timer(interval);
}

TimedEffect::~TimedEffect() {
    delete timer;
}

void TimedEffect::nextColor(Color* current) {
    if(timer->tick()) {
        tick(current);
    }
}

void TimedEffect::tick(Color* current) {
    return;
}

void TimedEffect::setSpeed(double speed) {
    this->timer->setInterval(speed);
}
