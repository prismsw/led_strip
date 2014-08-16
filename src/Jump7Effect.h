#ifndef JUMP7_EFFECT_H
#define JUMP7_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * Jump7Effect - switches between 7 fixed colors without gradual fading
 */
class Jump7Effect : public TimedEffect {
    private:
        Color* colors[7];

        int index;
    protected:
        virtual void tick();
        virtual int speedToInterval(double speed);
    public:
        Jump7Effect(double speed);

        virtual unsigned char id();
};
#endif
