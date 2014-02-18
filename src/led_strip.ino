#include "Color.h"

Color* color = new Color(0, 0, 0);
Color* targetColor = new Color(0, 0, 0);

const int rled = 2;
const int gled = 3;
const int bled = 4;

const int heart = 13;

const int button = 52;

// Light control
int mode = 0;
double fade = 0.1;
// Timer control
int interval = 1;
long lastUpdate = 0;

// Heartbeat
int pulse = 1000;
int heartState = LOW;
long lastBeat = 0;

// Button
int lastButtonState = 0;

void setup() {
    pinMode(rled, OUTPUT);
    pinMode(gled, OUTPUT);
    pinMode(bled, OUTPUT);

    pinMode(heart, OUTPUT);

    pinMode(button, INPUT);

    Serial.begin(9600);
}

void loop() {
    processIO();
    setColor(color);
    processButton();
    digitalWrite(heart, heartState);

    if(shouldTick(lastBeat, pulse)) {
        beat();
        lastBeat = millis();
    }

    if(shouldTick(lastUpdate, interval)) {
        int pot = analogRead(A15);
        if(mode == 1) {
            strip();
        }
        else if(mode == 10) {
            double hue = pot/1024.0 * 360.0;
            color->setH(hue);
        }
        else if(mode == 11) {
            double sat = pot/1024.0;
            color->setS(sat);
        }
        else if(mode == 12) {
            double val = pot/1024.0;
            color->setV(val);
        }
        lastUpdate = millis();
    }
}

void processButton() {
    int buttonState = digitalRead(button);
    if(buttonState != lastButtonState) {
        if(buttonState == LOW) {
            cycleMode();
            Serial.println(mode);
        }
    }
    lastButtonState = buttonState;
}

void cycleMode() {
    switch(mode) {
        case 1:
            mode =  10;
            break;
        case 12:
            mode = 0;
            break;
        default:
            mode++;
    }
}

void processIO() {
    while(Serial.available() > 0) {
        String cmd = Serial.readStringUntil(' ');

        if(cmd == "rgb") {
            color->setR(Serial.parseInt());
            color->setG(Serial.parseInt());
            color->setB(Serial.parseInt());
        }
        else if(cmd == "fade") {
            mode = 1;
            fade = Serial.parseFloat();
        }
        else if(cmd == "nofade") {
            mode = 0;
        }
        else if(cmd == "shiftH") {
            mode = 10;
        }
        else if(cmd == "shiftS") {
            mode = 11;
        }
        else if(cmd == "shiftV") {
            mode = 12;
        }
        else if(cmd == "hsv") {
            color->setH(Serial.parseFloat());
            color->setS(Serial.parseFloat());
            color->setV(Serial.parseFloat());
        }
        else if(cmd == "h") {
            color->setH(Serial.parseFloat());
        }
        else if(cmd == "s") {
            color->setS(Serial.parseFloat());
        }
        else if(cmd == "v") {
            color->setV(Serial.parseFloat());
        }
        else if(cmd == "print") {
            Serial.println(color->getR());
            Serial.println(color->getG());
            Serial.println(color->getB());
            Serial.println("");
        }
        else {
            Serial.println("Invalid command: " + cmd);
            return;
        }
        Serial.println(cmd);
    }
}

int setColor(Color* c) {
    analogWrite(rled, c->getR());
    analogWrite(gled, c->getG());
    analogWrite(bled, c->getB());
}

boolean shouldTick(long last, int interval) {
    unsigned long time = millis();

    long diff = time - last;

    return diff > interval;
}

void strip() {
    color->incH(fade);
    if(color->getH() >= 360 || color->getH() <= 0) {
        fade = -fade;
    }
}

void beat() {
    if(heartState == LOW) {
        heartState = HIGH;
    }
    else {
        heartState = LOW;
    }
}

