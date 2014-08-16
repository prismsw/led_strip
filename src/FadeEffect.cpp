#include "FadeEffect.h"
#include <Arduino.h>

FadeEffect::FadeEffect(const Color& color, double speed, double amount):TimedEffect(color, speed) {
    this->amount = amount;
    this->timer->setInterval(speedToInterval(speed));
}

unsigned char FadeEffect::id() {
    return 2;
}

void FadeEffect::tick() {
    currentColor->cycleH(amount);
}

int FadeEffect::speedToInterval(double speed) {
    return 100/speed;
}
