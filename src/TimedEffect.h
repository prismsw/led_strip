#ifndef TIMED_EFFECT_H
#define TIMED_EFFECT_H

#include "Color.h"
#include "Effect.h"

/**
 * TimedEffect - abstract class that executes a tick every x ms
 */
class TimedEffect : public Effect {
    private:
        int interval;
        long lastTick;
        
        bool shouldTick(long time);
    protected:
        /**
         * tick() - abstract function that executes arbitary code once every tick
         * @current: The current color
         *
         * This function is supposed to be implemented by the subclasses, similar to nextColor
         */
        virtual void tick(Color* current);

    public:
        TimedEffect(int interval);
        virtual ~TimedEffect() {};

        virtual void nextColor(Color* current);
};
#endif
