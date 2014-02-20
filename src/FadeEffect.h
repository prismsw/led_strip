#ifndef FADE_EFFECT_H
#define FADE_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

class FadeEffect : public TimedEffect {
    private:
        double amount;
    protected:
        virtual void tick(Color* current);
    public:
        FadeEffect(double amount, int interval);
};

#endif
