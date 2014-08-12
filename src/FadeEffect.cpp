#include "FadeEffect.h"
#include <Arduino.h>

FadeEffect::FadeEffect(Color color, double speed, double amount):TimedEffect(color, speed) {
    this->amount = amount;
    this->timer->setInterval(speedToInterval(speed));
}

void FadeEffect::tick() {
    currentColor->cycleH(amount);
}

int FadeEffect::speedToInterval(double speed) {
    return 100/speed;
}

unsigned char FadeEffect::id() {
    return 2;
}
