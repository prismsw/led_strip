#ifndef COLOR_H
#define COLOR_H

/**
 * Color - A simple wrapper around RGB/HSV values
 */
class Color {
    private:
        int r;
        int g;
        int b;

        double h;
        double s;
        double v;

        /**
         * boundedVal() - constrains a value between lower and upper bound
         * @val: The value to be constrained
         * @lbound: The lower bound
         * @ubound: The upper bound
         * Return: Either val, lbound or ubound
         */
        template <typename T>
        T boundedVal(T val, T lbound, T ubound) const {
            if(val < lbound) {
                return lbound;
            }
            else if(val > ubound) {
                return ubound;
            }
            else {
                return val;
            }
        }

        /**
         * boundedRGB() - constrains an arbitary R/G/B value (0-255)
         */
        int boundedRGB(int) const;

        /**
         * boundedH() - constrains an arbitary hue value (0-360)
         */
        double boundedH(double) const;

        /**
         * boundedSV() - constrains an arbitary saturation/value value (0-1)
         */
        double boundedSV(double) const;

        /**
         * updateHSV() - updates the HSV values to reflect the current RGB values
         *
         * This function has to be called every time the RGB values are changed
         */
        void updateHSV();

        /**
         * updateRGB() - updates the RGB values to reflect the current HSV values
         *
         * This function has to be called every time the HSV values are changed
         */
        void updateRGB();
    public:
        /**
         * Color() - constructs a new Color from RGB values
         * @r: red value
         * @g: green value
         * @b: blue value
         */
        Color(int r, int g, int b);

        /**
         * RGB getters
         */
        int getR() const;
        int getG() const;
        int getB() const;

        /**
         * RGB setters
         */
        void setR(int r);
        void setG(int g);
        void setB(int b);
        void setRGB(int r, int g, int b);

        void setColor(Color& other);

        /**
         * RGB increment functions
         *
         * Increments the R/G/B value by the specified amount
         * It is capped at 0 and 255 respectively
         */
        void incR(int r);
        void incG(int g);
        void incB(int b);

        /*
         * HSV getters
         */
        double getH() const;
        double getS() const;
        double getV() const;

        /*
         * HSV setters
         */
        void setH(double h);
        void setS(double s);
        void setV(double v);
        void setHSV(double h, double s, double v);

        /**
         * HSV increment functions
         *
         * Increments the H/S/V value by the specified amount
         * H is capped at 0/360
         * S/V are capped at 0/1
         */
        void incH(double);
        void incS(double);
        void incV(double);

        /**
         * cycleH - increments the hue value wraps around after 0/360
         * @h: the amount hue should be incremented
         */
        void cycleH(double h);

        bool operator== (const Color &other);
        bool operator!= (const Color &other);
};
#endif
