#include "FadeEffect.h"
#include <Arduino.h>

FadeEffect::FadeEffect(int amount, int interval) {
    this->amount = amount;
    this->interval = interval;
    this->lastFade = millis();
}

void FadeEffect::nextColor(Color* current) {
    long time = millis();
    if(shouldTick(time)) {
        current->cycleH(amount);
        lastFade = time;
    }
}

bool FadeEffect::shouldTick(long time) {
    return (time - lastFade) > interval;
}
