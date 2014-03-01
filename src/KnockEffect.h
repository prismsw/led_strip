#ifndef KNOCK_EFFECT_H
#define KNOCK_EFFECT_H

#include "Color.h"
#include "Effect.h"

class KnockEffect : public Effect {
    private:
        double increment;
        int treshold;
        long lastKnock = 0;
        int knockLength;

    public:
        KnockEffect(double increment, int treshold=5, int knockLength=100);
        virtual void nextColor(Color* current);
};

#endif
