#ifndef TIMED_EFFECT_H
#define TIMED_EFFECT_H

#include "Color.h"
#include "Effect.h"

class TimedEffect : public Effect {
    private:
        int interval;
        long lastTick;
        
        bool shouldTick(long time);
    protected:
        virtual void tick(Color* current);

    public:
        TimedEffect(int interval);
        virtual ~TimedEffect() {};

        virtual void nextColor(Color* current);
};
#endif
