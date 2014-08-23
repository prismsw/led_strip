#include "CrossFadeEffect.h"
#include <Arduino.h>

CrossFadeEffect::CrossFadeEffect(const Color& from, const Color& to, double speed):TimedEffect(from, speed) {
    this->fromColor = new Color(from);
    this->toColor = new Color(to);
    this->timer->setInterval(speedToInterval(speed));

    hAmount = max(0.3, (to.getH() - from.getH())/360.0);
    sAmount = max(0.3, (to.getS() - from.getS())) / 100;
    vAmount = max(0.3, (to.getV() - from.getV())) / 100;
}

CrossFadeEffect::~CrossFadeEffect() {
    delete fromColor;
    delete toColor;
}

unsigned char CrossFadeEffect::id() {
    return 7;
}
    
void CrossFadeEffect::tick() {
    double newH = currentColor->getH() + hAmount;
    double newS = currentColor->getS() + sAmount;
    double newV = currentColor->getV() + vAmount;

    if(overTarget(newH, toColor->getH(), hAmount)) {
        newH = toColor->getH();
    }

    if(overTarget(newS, toColor->getS(), sAmount)) {
        newS = toColor->getS();
    }

    if(overTarget(newV, toColor->getV(), vAmount)) {
        newV = toColor->getV();
    }

    currentColor->setHSV(newH, newS, newV);
}

int CrossFadeEffect::speedToInterval(double speed) {
    return 100/speed;
}

bool CrossFadeEffect::overTarget(double value, double target, double increment) {
    if(increment < 0) {
        if(value <= target) {
            return true;
        }
    }
    else {
        if(value >= target) {
            return true;
        }
    }

    return false;
}
