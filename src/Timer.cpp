#include "Timer.h"
#include <Arduino.h>

Timer::Timer(long interval) {
    this->interval = interval;
    this->lastTick = millis();
}

bool Timer::tick() {
    long m = millis();

    if((m - lastTick) > interval) {
        lastTick = m;
        return true;
    }

    return false;
}

void Timer::setInterval(long interval) {
    this->interval = interval;
}
