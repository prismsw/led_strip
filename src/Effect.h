#ifndef EFFECT_H
#define EFFECT_H

#include "Color.h"

/**
 * Effect - an interface for different ways of changing a color
 */
class Effect {
    protected:
        Color* currentColor;
    public:
        Effect();
        Effect(Color& color);
        virtual ~Effect();
        virtual void update() = 0;
        virtual Color* getColor();
        virtual void setColor(Color& c);
        virtual void setSpeed(double speed) = 0;
        virtual unsigned char id() = 0;
};

#endif
