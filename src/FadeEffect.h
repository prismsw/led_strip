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
        virtual int speedToInterval(double speed);
    public:
        FadeEffect(const Color& color, double speed, double amount);

        virtual unsigned char id();
};

#endif
