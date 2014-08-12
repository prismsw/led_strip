#include "Jump3Effect.h"

Jump3Effect::Jump3Effect(double speed):TimedEffect(speed) {
    this->timer->setInterval(speedToInterval(speed));
    index = 0;
    colors[0] = new Color(255,0,0);
    colors[1] = new Color(0,255,0);
    colors[2] = new Color(0,0,255);
};

void Jump3Effect::tick() {
    *currentColor = *colors[index];
    index = (index + 1) % 3;
}

int Jump3Effect::speedToInterval(double speed) {
    return 1000/speed;
}

unsigned char Jump3Effect::id() {
    return 3;
}
