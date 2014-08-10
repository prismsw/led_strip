#include "BlinkEffect.h"
#include <Arduino.h>

BlinkEffect::BlinkEffect(int interval):TimedEffect(interval) {}

bool BlinkEffect::isOff(Color* color) {
    return color->getV() == 0;
}

void BlinkEffect::setSpeed(double speed) {
    TimedEffect::setSpeed(1000 * 1/speed);
}

void BlinkEffect::tick(Color* current) {
    // The first time we have to set the color we are working with
    if(color == 0) {
        color = new Color(*current);
    }

    if(isOff(current)) {
        // Change the current (black) color to the stored one
        *current = *color;
    }
    else {
        // Store the current color and change the current one to black
        delete color;
        color = new Color(*current);
        *current = *black;
    }
}

unsigned char BlinkEffect::id() {
    return 1;
}
