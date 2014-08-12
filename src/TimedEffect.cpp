#include "TimedEffect.h"
#include <Arduino.h>

TimedEffect::TimedEffect(double speed):Effect() {
    this->timer = new Timer(speedToInterval(speed));
}

TimedEffect::TimedEffect(Color color, double speed):Effect(color) {
    this->timer = new Timer(speedToInterval(speed));
}

TimedEffect::~TimedEffect() {
    delete timer;
}

void TimedEffect::update() {
    if(timer->tick()) {
        tick();
    }
}

void TimedEffect::tick() {
    return;
}

void TimedEffect::setSpeed(double speed) {
    this->timer->setInterval(speedToInterval(speed));
}

int TimedEffect::speedToInterval(double speed) {
    return 1/speed;
}
