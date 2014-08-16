#include "Effect.h"

Effect::Effect() {
    this->currentColor = new Color(0,0,0);
}

Effect::~Effect() {
    delete currentColor;
}

Effect::Effect(const Color& color) {
    currentColor = new Color(color);
}

Color* Effect::getColor() {
    return currentColor;
}

void Effect::setColor(const Color& c) {
    *currentColor = c;
}
