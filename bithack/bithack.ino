#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <Timer.h>
Timer timer;

const int alphaSize = 26;

const int shortButton = 7;
const int longButton = 6;
const int stopButton = 15;

const int LEDSB = 5;
const int LEDLB = 4;
const int LEDSE = 16;
const int buzzer = 17; //

int startCountDown = 0;
int count = 0;
int randomIndex;

const int txPin = 43; //
const int rxPin = 44; //

volatile bool lb_pressed = false;
volatile bool sb_pressed = false;
volatile bool stop_pressed = false;

struct Alphabet{
  String letter;  
  String morseCode; 
};
Alphabet alphaProp[] = {
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
  tone(16, 783, 1000); //
}

void long_light(){
  lb_pressed = true;
  tone(16, 783, 3000); //
}

void stop() {
  stop_pressed = true;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  delay(10);
  }
  mySerial1.begin(9600, SERIAL_8N1, rxPin, txPin);
  player.volume(20); //

  
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);

  pinMode(longButton, INPUT_PULLUP);
  pinMode(LEDLB, OUTPUT);

  pinMode(stopButton, INPUT_PULLUP);
  pinMode(LEDSE, OUTPUT);

  pinMode(buzzer, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);
  attachInterrupt(digitalPinToInterrupt(longButton), long_light, FALLING);    
  attachInterrup(digitalPinToInterrupt(stopButton), stop, FALLING);

  pickRandomLetter();
}

void playMorseForLetter(String morseCode) {
  for (int i = 0; i < morseCode.length(); i++) {
    char bit = morseCode.charAt(i);
    if (bit == '0') {
      tone(16, 783, 1000);
      digitalWrite(LEDSB, HIGH);
      delay(1000);
      digitalWrite(LEDSB, LOW);
    } else if (bit == '1') {
      tone(16, 783, 3000);
      digitalWrite(LEDLB, HIGH);
      delay(3000);
      digitalWrite(LEDLB, LOW);
    }
  }
}

Alphabet currentLetter;
void pickRandomLetter() {
  randomIndex = random(0, alphaSize);

  Alphabet currentLetter = alphaProp[randomIndex];

  Serial.print("New round! Morse for letter: ");
  Serial.println(currentLetter.letter);
  Serial.print("Expected Morse code: ");
  Serial.println(currentLetter.morseCode);
  playMorseForLetter(currentLetter.morseCode);
}

void morseCheck() {
  bool found = false;
    if (buttonLog == alphaProp[randomIndex].morseCode) {
      Serial.println(alphaProp[randomIndex].letter);
      Serial.println("Correct!");
      found = true;
      player.play(1);
      delay(10000);
      player.stop();
      Serial.println("Play again?");
        if(stop_pressed); {
          pickRandomLetter();
        }
      break;
    }
  while (!found) {
    player.play(1); //use diff value for diff track number, whatever track corresponds to rick roll
    Serial.println("Incorrect input, try again");
    delay(10000);
    player.stop();
  }
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

