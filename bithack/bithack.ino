#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
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

String buttonLog = "";

void loop() {

  if (sb_pressed) {
    digitalWrite(LEDSB, HIGH);
    buttonLog += "0"; 
    Serial.println("Short button pressed. Log: " + buttonLog);
    delay(1000);
    digitalWrite(LEDSB, LOW);
    sb_pressed = false;
  }

  if (lb_pressed) {
    digitalWrite(LEDLB, HIGH);
    buttonLog += "1";
    Serial.println("Long button pressed. Log: " + buttonLog);
    delay(2000);
    digitalWrite(LEDLB, LOW);
    lb_pressed = false;
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
  {"N", "10"},
  {"O", "111"},
  {"P", "0110"},
  {"Q", "1101"},
  {"R", "010"},
  {"S", "000"},
  {"T", "1"},
  {"U", "001"},
  {"V", "0001"},
  {"W", "011"},
  {"X", "1001"},
  {"Y", "1011"},
  {"Z", "1100"},

}


