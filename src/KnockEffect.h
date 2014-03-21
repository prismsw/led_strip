#ifndef KNOCK_EFFECT_H
#define KNOCK_EFFECT_H

#include "Color.h"
#include "Effect.h"

/**
 * KnockEffect - recognizes taps/knocks and changes the color accordingly
 */
class KnockEffect : public Effect {
    private:
        double increment;
        int treshold;
        long lastKnock = 0;
        int knockLength;
        int doubleKnockTime;

    public:
        /**
         * KnockEffect() 
         * @increment: How much the hue is going to be increment each time
         * @treshold: The treshold value for recognizing a knock (0-1024)
         * @knockLength: For how long other inputs will be ignored after a knock (ms)
         * @doubleKnockTime: For how long after a knock, another knock will be counted as a double knock (ms)
         */
        KnockEffect(double increment, int treshold=5, int knockLength=100, int doubleKnockTime=200);
        virtual void nextColor(Color* current);
        virtual void setSpeed(double speed);
        virtual unsigned char id();
};

#endif
