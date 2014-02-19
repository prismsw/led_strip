#ifndef STATIC_EFFECT_H
#define STATIC_EFFECT_H

#include "Color.h"
#include "Effect.h"

class StaticEffect : public Effect {
    public:
        StaticEffect();

        virtual void nextColor(Color* current);
};

#endif
