#ifndef STATIC_EFFECT_H
#define STATIC_EFFECT_H

#include "Color.h"
#include "Effect.h"

/**
 * StaticEffect - an effect that simply does nothing
 */
class StaticEffect : public Effect {
    public:
        StaticEffect(Color color);

        virtual void update();
        virtual void setSpeed(double speed);
        virtual unsigned char id();
};

#endif
