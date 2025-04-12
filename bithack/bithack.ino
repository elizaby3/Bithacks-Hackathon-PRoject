#include <Timer.h>

Timer timer;

const int shortButton = 7;
const int longButton = 6;
//const int startEnd;
const int LEDSB = 5;
const int LEDLB = 4;
//const int LEDSE;
int startCountDown = 0;
int count = 0;

volatile bool sb_pressed = false;
bool sb_pressed_prev = false;
unsigned long sb_time = 0;
unsigned long sb_time_next = 0;

volatile bool lb_pressed = false;
bool lb_pressed_prev = false;
unsigned long lb_time = 0;
unsigned long lb_time_next = 0;


//turns on the green led for 1s when the short Button is pressed
void short_light() {
  sb_pressed = true;
}

void long_light(){
  lb_pressed = true;
  
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);
  pinMode(longButton, INPUT_PULLUP);
  pinMode(LEDLB, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);
  attachInterrupt(digitalPinToInterrupt(longButton), long_light, FALLING);

  Serial.println("Ready");
}


void loop() {

  if (sb_pressed) {
    digitalWrite(LEDSB, HIGH);
    delay(1000);
    digitalWrite(LEDSB, LOW);
    sb_pressed = false;
  }

  if (lb_pressed) {
    digitalWrite(LEDLB, HIGH);
    delay(2000);
    digitalWrite(LEDLB, LOW);
    lb_pressed = false;
  }
}
