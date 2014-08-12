#ifndef JUMP3_EFFECT_H
#define JUMP3_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * Jump3Effect - switches between 3 fixed colors without gradual fading
 */
class Jump3Effect : public TimedEffect {
    private:
        int index;
        Color* colors[3];
    protected:
        virtual void tick();
        virtual int speedToInterval(double speed);
    public:
        Jump3Effect(double speed);
        virtual unsigned char id();
};
#endif
