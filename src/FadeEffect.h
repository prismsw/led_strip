#ifndef FADE_EFFECT_H
#define FADE_EFFECT_H

#include "Color.h"
#include "Effect.h"

class FadeEffect : public Effect {
    private:
        int amount;
        int interval;
        long lastFade;

        bool shouldTick(long time);
    public:
        FadeEffect(int amount, int interval);
        virtual void nextColor(Color* current);
};

#endif
