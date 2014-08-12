#include "Effect.h"

Effect::Effect() {
    this->currentColor = new Color(0,0,0);
}

Effect::Effect(Color& color) {
    currentColor = new Color(color);
}

Color* Effect::getColor() {
    return currentColor;
}

void Effect::setColor(Color& c) {
    currentColor = new Color(c);
}

Effect::~Effect() {
    delete currentColor;
}
