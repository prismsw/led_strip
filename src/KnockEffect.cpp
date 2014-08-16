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
                // Set to black
                currentColor->setV(0);
            }
            else {
                // If the current color is black, set it to red
                if(currentColor->getV() == 0) {
                    currentColor->setRGB(255,0,0);
                }
                else {
                    currentColor->cycleH(increment);
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
