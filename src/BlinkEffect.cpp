#include "BlinkEffect.h"
#include <Arduino.h>

BlinkEffect::BlinkEffect(int interval):TimedEffect(interval) {}

bool BlinkEffect::isOff(Color* color) {
    return color->getV() == 0;
}

void BlinkEffect::tick(Color* current) {
    if(color == 0) {
        color = new Color(*current);
    }

    if(isOff(current)) {
        *current = *color;
    }
    else {
        delete color;
        color = new Color(*current);
        *current = *black;
    }
}
