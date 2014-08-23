#ifndef CROSS_FADE_EFFECT_H
#define CROSS_FADE_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * CrossFadeEffect - fades between the original and the new color until the new color is reached
 */
class CrossFadeEffect : public TimedEffect {
    private:
        Color* fromColor;
        Color* toColor;

        double hAmount;
        double sAmount;
        double vAmount;

        bool overTarget(double value, double target, double increment);
    protected:
        virtual void tick();
        virtual int speedToInterval(double speed);
    public:
        CrossFadeEffect(const Color& from, const Color& to, double speed);
        virtual ~CrossFadeEffect();

        virtual unsigned char id();
};

#endif
