#include "Color.h"
#include "Effect.h"
#include "StaticEffect.h"
#include "FadeEffect.h"
#include "BlinkEffect.h"
#include <IRremote.h>

Color* color = new Color(0, 0, 0);

const int R_PIN = 2;
const int G_PIN = 3;
const int B_PIN = 4;

const int HEART_PIN = 13;

const int IR_PIN = 11;

// Heartbeat
int pulse = 1000;
int heartState = LOW;
long lastBeat = 0;

// Effects
Effect* effect = new StaticEffect();

// IR
IRrecv irrecv(IR_PIN);
decode_results irresults;
int lastResult = 0x0;

void setup() {
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);

    pinMode(HEART_PIN, OUTPUT);

    Serial.begin(9600);

    irrecv.enableIRIn();
}

void loop() {
    handleIR();
    handleSerial();
    setColor(color);

    digitalWrite(HEART_PIN, heartState);

    if((millis() - lastBeat) > pulse) {
        blink(&heartState);
        lastBeat = millis();
    }

    effect->nextColor(color);
}

void setColor(Color* c) {
    analogWrite(R_PIN, c->getR());
    analogWrite(G_PIN, c->getG());
    analogWrite(B_PIN, c->getB());
}

void blink(int* var) {
    if(*var == LOW) {
        *var = HIGH;
    }
    else {
        *var = LOW;
    }
}


void handleSerial() {
    while(Serial.available() > 0) {
        String cmd = Serial.readStringUntil(' ');

        if(cmd == "rgb") {
            color->setR(Serial.parseInt());
            color->setG(Serial.parseInt());
            color->setB(Serial.parseInt());
        }
        else if(cmd == "fade") {
        }
        else if(cmd == "nofade") {
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

void handleIR() {
    if(irrecv.decode(&irresults)) {
        Serial.println(irresults.value, HEX);
        int val = irresults.value;
        if(val == 0xFFFFFFFF) {
            val = lastResult;
        }
        else {
            lastResult = val;
        }
        switchIRVal(val);
        irrecv.resume();
    }
}

void switchIRVal(int irval) {
    // I am so sorry...
    switch(irval) {
        case 0xFF3AC5:
            // br_up
            color->incV(0.07);
            break;
        case 0xFFBA45:
            // br_down
            color->incV(-0.07);
            break;
        case 0xFF827D:
            // next
            color->cycleH(60.0);
            break;
        case 0xFF02FD:
            color->setRGB(0,0,0);
            // power
            break;
        case 0xFF1AE5:
            // red
            color->setRGB(255,0,0);
            break;
        case 0xFF9A65:
            // green
            color->setRGB(0,255,0);
            break;
        case 0xFFA25D:
            // blue
            color->setRGB(0,0,255);
            break;
        case 0xFF22DD:
            // white
            color->setRGB(255,255,255);
            break;
        case 0xFF2AD5:
            // orange
            color->setRGB(255,20,0);
            break;
        case 0xFFAA55:
            // light green
            color->setRGB(0,255,100);
            break;
        case 0xFF926D:
            // navy blue
            color->setRGB(0,100,255);
            break;
        case 0xFF12ED:
            // skin1?
            color->setRGB(255,50,50);
            break;
        case 0xFF0AF5:
            // light orange
            color->setRGB(255,50,0);
            break;
        case 0xFF8A75:
            // light blue
            color->setRGB(0,210,255);
            break;
        case 0xFFB24D:
            // dark purple
            color->setRGB(140,0,255);
            break;
        case 0xFF32CD:
            // better white
            color->setRGB(255,200,140);
            break;
        case 0xFF38C7:
            // dark orange
            color->setRGB(64,5,0);
            break;
        case 0xFFB847:
            // ocean blue
            color->setRGB(0,190,180);
            break;
        case 0xFF7887:
            // pink
            color->setRGB(255,0,215);
            break;
        case 0xFFF807:
            // sky blue
            color->setRGB(0,255,255);
            break;
        case 0xFF18E7:
            // yellow
            color->setRGB(255,100,0);
            break;
        case 0xFF9867:
            // azur
            color->setRGB(0,127,255);
            break;
        case 0xFF58A7:
            // dark pink
            color->setRGB(255,0,120);
            break;
        case 0xFFD827:
            // whatever blue
            color->setRGB(0,220,255);
            break;
        case 0xFF28D7:
            // r_up
            color->incR(10);
            break;
        case 0xFFA857:
            // g_up
            color->incG(10);
            break;
        case 0xFF6897:
            // b_up
            color->incB(10);
            break;
        case 0xFFE817:
            // quick
            break;
        case 0xFF08F7:
            // r_down
            color->incR(-10);
            break;
        case 0xFF8877:
            // g_down
            color->incG(-10);
            break;
        case 0xFF48B7:
            // b_down
            color->incB(-10);
            break;
        case 0xFFC837:
            // slow
            break;
        case 0xFF30CF:
            // h_up
            color->incH(10.0);
            break;
        case 0xFFB04F:
            // s_up
            color->incS(0.04);
            break;
        case 0xFF708F:
            // v_up
            color->incV(0.04);
            break;
        case 0xFFF00F:
            // auto
            delete effect;
            effect = new StaticEffect();
            break;
        case 0xFF10EF:
            // h_down
            color->incH(-10.0);
            break;
        case 0xFF906F:
            // s_down
            color->incS(-0.04);
            break;
        case 0xFF50AF:
            // v_down
            color->incV(-0.04);
            break;
        case 0xFFD02F:
            // flash
            delete effect;
            effect = new BlinkEffect(300);
            break;
        case 0xFF20DF:
            // jump3
            break;
        case 0xFFA05F:
            // jump7
            break;
        case 0xFF609F:
            // fade3
            delete effect;
            effect = new FadeEffect(0.01, 1);
            break;
        case 0xFFE01F:
            // fade7
            break;
    }
}
