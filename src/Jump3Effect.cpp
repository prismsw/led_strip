#include "Jump3Effect.h"

Jump3Effect::Jump3Effect(int interval):TimedEffect(interval) {
    index = 0;
    colors[0] = new Color(255,0,0);
    colors[1] = new Color(0,255,0);
    colors[2] = new Color(0,0,255);
};

void Jump3Effect::tick(Color* current) {
    *current = *colors[index];
    index = (index + 1) % 3;
}
