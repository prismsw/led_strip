#include "KnockEffect.h"
#include "Pins.h"

KnockEffect::KnockEffect(double increment, int treshold, int knockLength) {
    this->increment = increment;
    this->treshold = treshold;
    this->knockLength = knockLength;
}

void KnockEffect::nextColor(Color* current) {
    int val = analogRead(KNOCK_PIN);
    long time = millis();

    if(time - lastKnock > knockLength) {
        if(val >= treshold) {
            lastKnock = time;
            current->cycleH(increment);
        }
    }
}
