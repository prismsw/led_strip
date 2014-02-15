const int rled = 2;
const int gled = 3;
const int bled = 4;

const int heart = 13;

int br = 0;
int fade = 5;
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
}

void loop() {
  analogWrite(rled, br);
  analogWrite(gled, br);
  analogWrite(bled, br);
  digitalWrite(heart, heartState);
  

  if(shouldTick(lastBeat, pulse)){
    beat();
    lastBeat = millis();
  }
  
  if(shouldTick(lastUpdate, interval)) {
    strip();
    lastUpdate = millis();
  }
}
boolean shouldTick(long last, int interval) {
  unsigned long time = millis();
  
  long diff = time - last;
  
  return diff > interval;
}

void strip() {
  br = br + fade;
  if(br <= 0 || br >= 255) {
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
