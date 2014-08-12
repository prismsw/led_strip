#include "BlinkEffect.h"
#include <Arduino.h>

BlinkEffect::BlinkEffect(Color color, double speed):TimedEffect(color, speed) {
    this->originalColor = new Color(color);
    this->timer->setInterval(speedToInterval(speed));
}

BlinkEffect::~BlinkEffect() {
    delete originalColor;
    delete black;
}

int BlinkEffect::speedToInterval(double speed) {
    return 1000/speed;
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

unsigned char BlinkEffect::id() {
    return 1;
}
