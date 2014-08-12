#ifndef BLINK_EFFECT_H
#define BLINK_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * BlinKEffect - flashes between the color and black
 */
class BlinkEffect : public TimedEffect {
    private:
        bool off = false;
        Color* originalColor;
        Color* black = new Color(0,0,0);
    protected:
        virtual void tick();
    public:
        BlinkEffect(Color color, double speed);
        virtual ~BlinkEffect();
        virtual int speedToInterval(double speed);
        virtual unsigned char id();
};

#endif
