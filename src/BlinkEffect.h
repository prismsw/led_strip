#ifndef BLINK_EFFECT_H
#define BLINK_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * BlinKEffect - flashes between the color and black
 */
class BlinkEffect : public TimedEffect {
    private:
        Color* color = 0;
        Color* black = new Color(0,0,0);

        bool isOff(Color* color);
    protected:
        virtual void tick(Color* current);
    public:
        BlinkEffect(int interval);
};

#endif
