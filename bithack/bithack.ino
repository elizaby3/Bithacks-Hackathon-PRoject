#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int shortButton = 7;
const int longButton;
const int startEnd;
const int LEDSB = 15;
const int LEDLB;
const int LEDSE;
const int rxPin = ;
const int txPin = ;

int startCountDown;
HardwareSerial mySerial1(1);
DFRobotDFPlayerMini player;

//turns on the green led for 1s when the short Button is pressed
void short_light() {
  digitalWrite(LEDSB, HIGH);
  tone(3, 783, 1000);
  startCountDown = 1;
  digitalWrite(LEDSB, LOW);
  
}

void long_light() {
  digitalWrite(LEDLB, HIGH);
  tone(3, 783, 3000);

  startCountDown = 1;
  digitalWrite(LEDLB, LOW);
}

void setup() {
  pinMode(shortButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);
  pinMode(longButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(longButton), long_light, FALLING);

  player.volume(20);
  player.play(1);
  mySerial1.begin(9600, SERIAL_8N1, rxPin, txPin);

}

int longLightCount = 3000;

void loop() {

  if(startCountDown && longLightCount > 0) {
    longLightCount--;
    digitalWrite(LEDLB, HIGH);
  }else{
    digitalWrite(LEDLB, LOW);
    startCountDown = 0;
  }
}
