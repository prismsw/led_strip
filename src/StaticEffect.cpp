#include "StaticEffect.h"

StaticEffect::StaticEffect(const Color& color):Effect(color) {}

void StaticEffect::update() {
    return;
}

void StaticEffect::setSpeed(double speed) {
    return;
}

unsigned char StaticEffect::id() {
    return 0;
}
