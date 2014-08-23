#ifndef TRIPWIRE_EFFECT_H
#define TRIPWIRE_EFFECT_H

#include "Color.h"
#include "Effect.h"
#include "Timer.h"
#include "USTripwire.h"

#include <NewPing.h>

/**
 * TripwireEffect - activates the LEDs when ultrasonic tripwire is breached
 */
class TripwireEffect : public Effect {
    private:
        USTripwire* tripwire;
        Timer *usTimer;

        Color* onColor;
        Color* black;

        int interval;
    public:
        TripwireEffect(const Color& color, int treshold=120, int interval=100);
        ~TripwireEffect();

        virtual void update();
        virtual void setSpeed(double speed);

        virtual unsigned char id();
};

#endif
