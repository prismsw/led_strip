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
        int doubleKnockTime;

    public:
        KnockEffect(double increment, int treshold=5, int knockLength=100, int doubleKnockTime=200);
        virtual void nextColor(Color* current);
};

#endif
