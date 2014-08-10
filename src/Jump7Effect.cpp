#include "Jump7Effect.h"

Jump7Effect::Jump7Effect(int interval):TimedEffect(interval) {
    index = 0;
    colors[0] = new Color(255,0,0);
    colors[1] = new Color(255,20,0);
    colors[2] = new Color(255,100,0);
    colors[3] = new Color(0,255,0);
    colors[4] = new Color(0,210,255);
    colors[5] = new Color(0,0,255);
    colors[6] = new Color(255,0,120);
};

void Jump7Effect::tick(Color* current) {
    *current = *colors[index];
    index = (index + 1) % 7;
}

void Jump7Effect::setSpeed(double speed) {
    TimedEffect::setSpeed(1000 * 1/speed);
}

unsigned char Jump7Effect::id() {
    return 4;
}
