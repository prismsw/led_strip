#include "KnockEffect.h"
#include "Pins.h"

KnockEffect::KnockEffect(double increment, int treshold, int knockLength, int doubleKnockTime) {
    this->increment = increment;
    this->treshold = treshold;
    this->knockLength = knockLength;
    this->doubleKnockTime = doubleKnockTime;
}

void KnockEffect::nextColor(Color* current) {
    int val = analogRead(KNOCK_PIN);
    long time = millis();

    if(time - lastKnock > knockLength) {
        if(val >= treshold) {
            if(((time - lastKnock) - knockLength) <= doubleKnockTime) {
                current->setV(0);
            }
            else {
                if(current->getV() == 0) {
                    current->setRGB(255,0,0);
                }
                else {
                    current->cycleH(increment);
                }
            }

            lastKnock = time;
        }
    }
}
