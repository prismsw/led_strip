#ifndef BLINK_EFFECT_H
#define BLINK_EFFECT_H

#include "Color.h"
#include "TimedEffect.h"

/**
 * BlinKEffect - flashes between the color and black
 */
class BlinkEffect : public TimedEffect {
    private:
        Color* originalColor;
        Color* black = new Color(0,0,0);

        bool off = false;
    protected:
        virtual void tick();
        virtual int speedToInterval(double speed);
    public:
        BlinkEffect(const Color& color, double speed);
        virtual ~BlinkEffect();

        virtual unsigned char id();
};

#endif
