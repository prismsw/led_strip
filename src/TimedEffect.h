#ifndef TIMED_EFFECT_H
#define TIMED_EFFECT_H

#include "Color.h"
#include "Effect.h"
#include "Timer.h"

/**
 * TimedEffect - abstract class that executes a tick every x ms
 */
class TimedEffect : public Effect {
    protected:
        Timer *timer;
        /**
         * tick() - abstract function that executes arbitary code once every tick
         * @current: The current color
         */
        virtual void tick();
        virtual int speedToInterval(double speed);

    public:
        TimedEffect(double speed);
        TimedEffect(Color color, double speed);
        virtual ~TimedEffect();

        virtual void update();

        virtual void setSpeed(double speed);

        virtual unsigned char id() = 0;
};
#endif
