#ifndef TIMER_H
#define TIMER_H

class Timer {
    public:
        Timer(long interval);
        bool tick();
        void setInterval(long interval);

    private:
        long interval;
        long lastTick;
};

#endif
