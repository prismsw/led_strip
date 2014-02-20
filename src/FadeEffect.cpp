#include "FadeEffect.h"
#include <Arduino.h>

FadeEffect::FadeEffect(double amount, int interval):TimedEffect(interval) {
    this->amount = amount;
}

void FadeEffect::tick(Color* current) {
    current->cycleH(amount);
}
