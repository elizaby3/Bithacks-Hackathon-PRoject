#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <timer.h>

const int shortButton = 6;
//const int longButton;
//const int startEnd;
const int LEDSB = 5;
//const int LEDLB;
//const int LEDSE;

int count = 0;
HardwareSerial mySerial1(1);
DFRobotDFPlayerMini player;


//turns on the green led for 1s when the short Button is pressed
void short_light() {
  count++;
  Serial.write("activated\n");

  if (count%2 == 0) {
    digitalWrite(LEDSB, LOW);
  } else {
    digitalWrite(LEDSB, HIGH);
  }

//turns on the green led for 1s when the short Button is pressed
void short_light() {
  digitalWrite(LEDSB, HIGH);
  tone(3, 783, 1000);
  startCountDown = 1;
}

void long_light() {
  digitalWrite(LEDLB, HIGH);
  tone(3, 783, 3000);

  startCountDown = 1;
  longLightCount = 1;
}

void setup() {
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);

  Serial.begin(115200);

}

void loop() {

  if(startCountDown && longLightCount > 0) {
    longLightCount--;
    digitalWrite(LEDLB, HIGH);

  }else{
    digitalWrite(LEDLB, LOW);
    startCountDown = 0;
  }
}

{"N", "10"};
{"O", "111"};
{"P", "0110"};
{"Q", "1101"};
{"R", "010"};
{"S", "000"};
{"T", "1"};
{"U", "001"};
{"V", "0001"};
{"W", "011"};
{"X", "1001"};
{"Y", "1011"};
{"Z", "1100"};






