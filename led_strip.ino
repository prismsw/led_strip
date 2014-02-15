#include "Color.h"

Color* color = new Color(0, 0, 0);
Color* targetColor = new Color(0, 0, 0);

const int rled = 2;
const int gled = 3;
const int bled = 4;

const int heart = 13;

int mode = 0;
int fade = 1;
int interval = 10;
long lastUpdate = 0;

int pulse = 1000;
int heartState = LOW;
long lastBeat = 0;

void setup() {
  pinMode(rled, OUTPUT);
  pinMode(gled, OUTPUT);
  pinMode(bled, OUTPUT);

  pinMode(heart, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  processIO();
  setColor(color);
  digitalWrite(heart, heartState);
  delay(1000);
  beat();
  delay(1000);
  
  if(shouldTick(lastBeat, pulse)){
    beat();
    lastBeat = millis();
  }
  
  if(shouldTick(lastUpdate, interval)) {
    switch(mode) {
      case 1:
        strip();
        break;
    }
    lastUpdate = millis();
  }
}

void processIO() {
 while(Serial.available() > 0) {
    int action = Serial.parseInt();
    
    switch(action) {
      case 0:
        color->setR(Serial.parseInt());
        color->setG(Serial.parseInt());
        color->setB(Serial.parseInt());
        mode = 0;
        break;
      case 1:
        mode = 1;
        break;
      case 2:
        color->setH(Serial.parseFloat());
        color->setS(Serial.parseFloat());
        color->setV(Serial.parseFloat());
        mode = 0;
        break;
    }
    
    Serial.println(color->getR());
    Serial.println(color->getG());
    Serial.println(color->getB());
    Serial.println("");
    
    if(Serial.read() == '\n') {
      return;
    }
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
