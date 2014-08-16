#ifndef TRIPWIRE_EFFECT_H
#define TRIPWIRE_EFFECT_H

#include "Color.h"
#include "Effect.h"
#include "Pins.h"
#include "Timer.h"

#include <NewPing.h>

/**
 * TripwireEffect - activates the LEDs when ultrasonic tripwire is breached
 */
class TripwireEffect : public Effect {
    private:
        NewPing *sonar;
        Timer *usTimer;

        Color* onColor;
        Color* black;

        int treshold;
        int interval;
        int lockTime;

        long lastTripped;
        bool isTripped = false;

    public:
        TripwireEffect(const Color& color, int treshold=120, int interval=100, int lockTime=500);
        ~TripwireEffect();

        virtual void update();
        virtual void setSpeed(double speed);

        virtual unsigned char id();
};

#endif
