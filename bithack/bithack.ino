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

struct Alphabet{ //creates the "dictionary" that allows to access the features of each letter in the alphabet
  String letter;  //accesses the letter
  String morseCode; //accesses the morse code that corresponds to each letter 
  //the morseCode is integers as a string because we'll use the compare function
}

Alphabet alphaProp[] = { //creates an array that includes all letters of the alphabet and its properties as properties 
  {"A", "01"},
  {"B", "1000"},
  {"C", "1010"},
  {"D", "100"},
  {"E", "0"},
  {"F", "0011"},
  {"G", "110"},
  {"H", "0000"},
  {"I", "00"},
  {"J", "0111"},
  {"K", "101"},
  {"L", "010"},
  {"M", "11"}, 

  


}

