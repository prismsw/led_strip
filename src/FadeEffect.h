#ifndef FADE_EFFECT_H
#define FADE_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * FadeEffect - gradually moves the color through the whole spectrum
 */
class FadeEffect : public TimedEffect {
    private:
        double amount;
    protected:
        virtual void tick();
    public:
        FadeEffect(Color color, double speed, double amount);
        virtual int speedToInterval(double speed);
        virtual unsigned char id();
};

#endif
