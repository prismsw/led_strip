#include "Pins.h"
#include "Color.h"
#include "Effect.h"
#include "StaticEffect.h"
#include "FadeEffect.h"
#include "BlinkEffect.h"
#include "KnockEffect.h"
#include "Jump3Effect.h"
#include "Jump7Effect.h"
#include <IRremote.h>

#define API_BUFFER_LENGTH 8

Color* color = new Color(0, 0, 0);

// Heartbeat
int pulse = 1000;
int heartState = LOW;
long lastBeat = 0;

// Effects
Effect* effect = new StaticEffect();
double speed = 1.0;

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

void incSpeed(double val) {
    speed = speed + val;

    if(speed <= 0.1) {
        speed = 0.1;
    }
    else if(speed >= 8.0) {
        speed = 8.0;
    }

    effect->setSpeed(speed);
}


void handleSerial() {
    while(Serial.available() > 0) {
        byte buffer[API_BUFFER_LENGTH];
        Serial.readBytes((char*)buffer,API_BUFFER_LENGTH);
        
        byte action = buffer[0];

        switch(action) {
        case 0:
            // RGB
        {
            int r = buffer[1];
            int g = buffer[2];
            int b = buffer[3];

            setStaticRGB(r,g,b);
        }
            break;
        case 1:
            // HSV
        {
            int h = buffer[1] / 255.0 * 360.0;
            int s = buffer[2] / 255.0;
            int v = buffer[3] / 255.0;
            
            color->setHSV(h,s,v);
        }
            break;
        case 2:
            // Mode
        {
            byte mode = buffer[1];

            switch(mode) {
            case 0:
                delete effect;
                effect = new StaticEffect();
                break;
            case 1:
                delete effect;
                effect = new BlinkEffect(1000 * 1/speed);
                break;
            case 2:
                delete effect;
                effect = new FadeEffect(0.1 * speed, 1);
                break;
            case 3:
                delete effect;
                effect = new Jump3Effect(1000 * 1/speed);
                break;
            case 4:
                delete effect;
                effect = new Jump7Effect(1000 * 1/speed);
                break;
            case 5:
                delete effect;
                effect = new KnockEffect(60.0);
                break;
            }
            break;
        }
        case 3:
            // Speed
        {
            // Scale speed from 0-255 to 0.1-8.0
            speed = 0.1 + buffer[1] / 255.0 * 7.9;
            effect->setSpeed(speed);
            break;
        }

        case 10:
            // State
        {
            //   0    1  2  3    4    5      6-7
            // [type][r][g][b][speed][mode]reserved
            byte outBuffer[API_BUFFER_LENGTH] = {0};
            outBuffer[0] = 10;

            outBuffer[1] = color->getR();
            outBuffer[2] = color->getG();
            outBuffer[3] = color->getB();

            outBuffer[4] = (unsigned char) ((speed-0.1) / 7.9 * 255);

            /**
             * Static   = 0
             * Blink    = 1
             * Fade     = 2
             * Jump3    = 3
             * Jump7    = 4
             * Knock    = 5
             */
            outBuffer[5] = effect->id();
            Serial.write(outBuffer, API_BUFFER_LENGTH);
            break;
        }
        }
    }
}

void handleIR() {
    if(irrecv.decode(&irresults)) {
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

void setStaticRGB(int r, int g, int b) {
    delete effect;
    effect = new StaticEffect();

    color->setRGB(r, g, b);
}

void switchIRVal(int irval) {
    // I am so sorry...
    switch(irval) {
        case 0xFF3AC5:
            // br_up
            color->incV(0.10);
            break;
        case 0xFFBA45:
            // br_down
            if(color->getV() <= 0.05) {
                color->incV(-0.01);
            }
            else if(color->getV() <= 0.1) {
                color->incV(-0.05);
            }
            else {
                color->incV(-0.10);
            }
            break;
        case 0xFF827D:
            // next
            color->cycleH(60.0);
            break;
        case 0xFF02FD:
            setStaticRGB(0,0,0);
            // power
            break;
        case 0xFF1AE5:
            // red
            setStaticRGB(255,0,0);
            break;
        case 0xFF9A65:
            // green
            setStaticRGB(0,255,0);
            break;
        case 0xFFA25D:
            // blue
            setStaticRGB(0,0,255);
            break;
        case 0xFF22DD:
            // white
            setStaticRGB(255,255,255);
            break;
        case 0xFF2AD5:
            // orange
            setStaticRGB(255,20,0);
            break;
        case 0xFFAA55:
            // light green
            setStaticRGB(0,255,100);
            break;
        case 0xFF926D:
            // navy blue
            setStaticRGB(0,100,255);
            break;
        case 0xFF12ED:
            // skin1?
            setStaticRGB(255,50,50);
            break;
        case 0xFF0AF5:
            // light orange
            setStaticRGB(255,50,0);
            break;
        case 0xFF8A75:
            // light blue
            setStaticRGB(0,210,255);
            break;
        case 0xFFB24D:
            // dark purple
            setStaticRGB(140,0,255);
            break;
        case 0xFF32CD:
            // better white
            setStaticRGB(255,200,140);
            break;
        case 0xFF38C7:
            // dark orange
            setStaticRGB(64,5,0);
            break;
        case 0xFFB847:
            // ocean blue
            setStaticRGB(0,190,180);
            break;
        case 0xFF7887:
            // pink
            setStaticRGB(255,0,215);
            break;
        case 0xFFF807:
            // sky blue
            setStaticRGB(0,255,255);
            break;
        case 0xFF18E7:
            // yellow
            setStaticRGB(255,100,0);
            break;
        case 0xFF9867:
            // azur
            setStaticRGB(0,127,255);
            break;
        case 0xFF58A7:
            // dark pink
            setStaticRGB(255,0,120);
            break;
        case 0xFFD827:
            // whatever blue
            setStaticRGB(0,220,255);
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
            incSpeed(0.1);
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
            incSpeed(-0.1);
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
            effect = new BlinkEffect(1000 * 1/speed);
            break;
        case 0xFF20DF:
            // jump3
            delete effect;
            effect = new KnockEffect(60.0);
            break;
        case 0xFFA05F:
            // jump7
            delete effect;
            effect = new Jump7Effect(1000 * 1/speed);
            break;
        case 0xFF609F:
            // fade3
            delete effect;
            effect = new FadeEffect(0.1 * speed, 1);
            break;
        case 0xFFE01F:
            // fade7
            delete effect;
            effect = new FadeEffect(0.01 * speed, 1);
            break;
    }
}
