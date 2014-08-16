#ifndef TIMER_H
#define TIMER_H

class Timer {
    private:
        long interval;
        long lastTick;
    public:
        Timer(long interval);

        bool tick();
        void setInterval(long interval);
};

#endif
