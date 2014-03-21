#ifndef EFFECT_H
#define EFFECT_H

/**
 * Effect - an interface for different ways of changing a color
 */
class Effect {
    public:
        /**
         * nextColor() - updates the passed color
         * @current: the color to be updated
         */
        virtual void nextColor(Color* current) = 0;
        virtual void setSpeed(double speed) = 0;
        virtual unsigned char id() = 0;
};

#endif
