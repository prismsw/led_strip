#ifndef JUMP3_EFFECT_H
#define JUMP3_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

class Jump3Effect : public TimedEffect {
    private:
        int index;
        Color* colors[3];
    protected:
        virtual void tick(Color* current);

    public:
        Jump3Effect(int interval);
};
#endif
