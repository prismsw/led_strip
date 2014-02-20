#include "TimedEffect.h"
#include <Arduino.h>

TimedEffect::TimedEffect(int interval) {
    this->interval = interval;
    this->lastTick = millis();
}

void TimedEffect::nextColor(Color* current) {
    long time = millis();
    if(shouldTick(time)) {
        tick(current);
        lastTick = time;
    }
}

void TimedEffect::tick(Color* current) {
    return;
}

bool TimedEffect::shouldTick(long time) {
    return (time - lastTick) > interval;
}
