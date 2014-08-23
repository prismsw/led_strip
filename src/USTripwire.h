#ifndef US_TRIPWIRE_H
#define US_TRIPWIRE_H

#include <Arduino.h>
#include <NewPing.h>

/**
 * SensorState - holds the current sensor state for our state machine
 * Format: First_Second
 * R: Right
 * L: Left
 * C: Clear
 */
enum SensorState {
    C_C,
    R_C,
    R_L,
    C_L,
    L_C,
    L_R,
    C_R
};

enum SensorEvent {
    NONE,
    R_IN,
    R_OUT,
    L_IN,
    L_OUT
};

enum Event {
    NOTHING,
    ENTERED,
    EXITED
};

class USTripwire {
    private:
        NewPing *usLeft;
        NewPing *usRight;
        byte treshold;


        SensorState state = C_C;
        byte inCount;

        void processEvent(Event e);
        SensorEvent processLeft();
        SensorEvent processRight();
        Event processStateMachine(SensorEvent e);

    public:
        USTripwire(byte inCount=0, byte treshold=120, byte maxDist=200);
        ~USTripwire();

        byte getCount() const;
        SensorState getState() const;

        Event update();
};

#endif
