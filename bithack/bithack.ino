#include <Timer.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>

const int alphaSize = 26;

const int shortButton = 7;
const int longButton = 6;
const int stopButton = 15;

const int LEDSB = 5; //LED short button
const int LEDLB = 4; //LED long button 
const int LEDSE = 16; //LED start and end

int startCountDown = 0;
int count = 0;
int randomIndex;

volatile bool lb_pressed = false;
volatile bool sb_pressed = false;
volatile bool stop_pressed = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

struct Alphabet{
  String letter;  
  String morseCode; 
};
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
};
String buttonLog = "";

void short_light() {
  sb_pressed = true;
}

void long_light(){
  lb_pressed = true;
}

void stop() {
  stop_pressed = true;
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

  pinMode(stopButton, INPUT_PULLUP);
  pinMode(LEDSE,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);
  attachInterrupt(digitalPinToInterrupt(longButton), long_light, FALLING);      //setup for pinmods and interrupts
  attachInterrupt(digitalPinToInterrupt(stopButton), stop, FALLING);

  lcd.init();
  lcd.backlight();

  pickRandomLetter();
}



void pickRandomLetter() {
  randomIndex = random(0, alphaSize); // Get random index from 0 to alphaSize - 

  Alphabet currentLetter = alphaProp[randomIndex];

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Morse for letter: ");
  lcd.setCursor(1,0);
  lcd.print(currentLetter.letter);
  delay(10000);
}


void morseCheck() {
  bool found = false;
    if (buttonLog == alphaProp[randomIndex].morseCode) {
      Serial.println(alphaProp[randomIndex].letter);
      found = true;
    }
  if (!found) {
    Serial.println("No match found.");
  }

  pickRandomLetter();

}

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

  if (stop_pressed) {
    morseCheck();
    digitalWrite(LEDSE, HIGH);
    delay(1000);
    digitalWrite(LEDSE, LOW);
    stop_pressed = false;
  }
}