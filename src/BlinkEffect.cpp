#include "BlinkEffect.h"
#include <Arduino.h>

BlinkEffect::BlinkEffect(const Color& color, double speed):TimedEffect(color, speed) {
    this->originalColor = new Color(color);
    this->timer->setInterval(speedToInterval(speed));
}

BlinkEffect::~BlinkEffect() {
    delete originalColor;
    delete black;
}

unsigned char BlinkEffect::id() {
    return 1;
}

void BlinkEffect::tick() {
    off = !off;

    if(off) {
        *currentColor = *originalColor;
    }
    else {
        *currentColor = *black;
    }
}

int BlinkEffect::speedToInterval(double speed) {
    return 1000/speed;
}
