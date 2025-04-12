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

HardwareSerial mySerial1(1);
DFRobotDFPlayerMini player;

//turns on the green led for 1s when the short Button is pressed
void short_light() {
  digitalWrite(LEDSB, HIGH);
  tone(3, 783, 500);
  delay(1000);
  digitalWrite(LEDSB, LOW);
  
}

void long_light() {
  digitalWrite(LEDLB, HIGH);
  delay(1000);
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

void loop() {
  // put your main code here, to run repeatedly:

}
