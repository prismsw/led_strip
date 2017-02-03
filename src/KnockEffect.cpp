#include "KnockEffect.h"
#include "Pins.h"

KnockEffect::KnockEffect(const Color& color, double increment, int treshold, int knockLength, int doubleKnockTime):Effect(color) {
    this->increment = increment;
    this->treshold = treshold;
    this->knockLength = knockLength;
    this->doubleKnockTime = doubleKnockTime;
}

void KnockEffect::update() {
    int val = analogRead(KNOCK_PIN);
    long time = millis();

    // If the time that passed since the last knock is greater than our waiting time
    if((time - lastKnock) > knockLength) {
        // We only care if the value from the knock sensor exceeds the treshold
        if(val >= treshold) {
            // If the time that passed since the end of the last knock exceeds the double knock time
            if(((time - lastKnock) - knockLength) <= doubleKnockTime) {
                // If it is off turn it on and vice versa
                if(currentColor->getV() == 0) {
                    currentColor->setRGB(255,255,255);
                } else {
                    currentColor->setRGB(0,0,0);
                }
            }

            // Update the time of the last knock
            lastKnock = time;
        }
    }
}

void KnockEffect::setSpeed(double speed) {
    return;
}

unsigned char KnockEffect::id() {
    return 5;
}
