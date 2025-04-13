#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define I2C_SDA 10
#define I2C_SDL 11

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int alphaSize = 25;

const int shortButton = 7;
const int longButton = 6;
const int stopButton = 15;
const int modeButton = 8;

const int LEDSB = 5;
const int LEDLB = 4;
const int LEDSE = 16;
const int LEDM = 18;

const int buzzer = 17; ///

int startCountDown = 0;
int count = 0;
int randomIndex = -1;

const int txPin = 43; //
const int rxPin = 44; //

volatile bool lb_pressed = false;
volatile bool sb_pressed = false;
volatile bool stop_pressed = false;
volatile bool learning = true;

DFRobotDFPlayerMini player;

HardwareSerial mySerial1(1);

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

Alphabet currentLetter;

String buttonLog = "";

int C3 = 523;
int D3 = 587;
int E3 = 659;
int F3 = 698;
int G3 = 783;
int A_3=880;

int DT = 1175;
int FB = 350;
int GB = 392;

int Aflat = 831; //415
int Alf = 415;
int Bflat = 932; //466
int Blf = 466;
int Eflat = 622; //311
int Elf = 311;


void congrats() {
int EN = 200*0.75;
int SN = 100*0.75;
int QN = 400*0.75;
int DotEN = 300*0.755;
  tone(buzzer, Elf, EN);
  tone(buzzer, Blf, SN);
  tone(buzzer, F3, EN);
  tone(buzzer, F3, EN);
  tone(buzzer, Eflat, SN); 
  tone(buzzer, F3, EN);
  tone(buzzer, Eflat, EN);
  tone(buzzer, Blf, QN);

  tone(buzzer, FB, EN);
  tone(buzzer, Alf, SN);
  tone(buzzer, C3, EN);
  tone(buzzer, C3,EN);
  tone(buzzer, Blf, EN);
  tone(buzzer, C3, SN);
  tone(buzzer, Eflat, EN);
  tone(buzzer, F3, DotEN);
  tone(buzzer, Blf, SN); 
  tone(buzzer, Blf, EN);

  tone(buzzer, G3, EN);
  tone(buzzer, F3, EN);
  tone(buzzer, Eflat, EN);
  tone(buzzer, Bflat, EN);
  tone(buzzer, Bflat, SN);
  tone(buzzer, G3, EN);
  tone(buzzer, F3, EN);
  tone(buzzer, C3, EN);

  tone(buzzer, Elf, EN);
  tone(buzzer, Blf, EN);
  tone(buzzer, Eflat, EN);
  tone(buzzer, FB, EN);
  tone(buzzer, GB, 800*0.75);
}

void lost() {
  tone(buzzer, C3, 2*50);
  tone(buzzer, D3, 2*50);
  tone(buzzer, F3, 2*50);
  tone(buzzer, D3, 2*50);

  tone(buzzer, A_3, 6*50);
  tone(buzzer, A_3, 6*50);
  tone(buzzer, G3, 12*50);

  tone(buzzer, C3, 2*50);
  tone(buzzer, D3, 2*50);
  tone(buzzer, F3, 2*50);
  tone(buzzer, D3, 2*50);

  tone(buzzer, G3, 6*50);
  tone(buzzer, G3, 6*50);
  tone(buzzer, F3, 6*50);
  tone(buzzer, E3, 2*50);
  tone(buzzer, D3, 4*50);

  tone(buzzer, C3, 2*50);
  tone(buzzer, D3, 2*50);
  tone(buzzer, F3, 2*50);
  tone(buzzer, D3, 2*50);

  tone(buzzer, F3, 8*50);
  tone(buzzer, G3, 4*50);
  tone(buzzer, E3, 6*50);
  tone(buzzer, D3, 2*50);
  tone(buzzer, C3, 8*50);
  tone(buzzer, C3, 2*50);
  tone(buzzer, G3, 8*50);
  tone(buzzer, F3, 16*50);

}

void short_light() {
  sb_pressed = true;
  Serial.println("Short");
  //tone(16, 783, 1000); //
}

void long_light(){
  lb_pressed = true;
  Serial.println("Long");
  //tone(16, 783, 3000); //
}

void stop_light() {
  Serial.println("stop");
  stop_pressed = true;
}

void set_mode() {
  if (learning) {
    learning = false;
    digitalWrite(LEDM, HIGH);
  } else {
    learning = true;
    digitalWrite(LEDM, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  delay(10);
  }

  /*mySerial1.begin(9600, SERIAL_8N1, rxPin, txPin);
  player.volume(20);*/ 
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);

  pinMode(longButton, INPUT_PULLUP);
  pinMode(LEDLB, OUTPUT);

  pinMode(stopButton, INPUT_PULLUP);
  pinMode(LEDSE, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(modeButton, INPUT_PULLUP);
  pinMode(LEDM, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);
  attachInterrupt(digitalPinToInterrupt(longButton), long_light, FALLING);    
  attachInterrupt(digitalPinToInterrupt(stopButton), stop_light, FALLING);
  attachInterrupt(digitalPinToInterrupt(modeButton), set_mode, FALLING);

  Wire.begin(I2C_SDA, I2C_SDL);
  lcd.init();
  lcd.backlight();

  pickRandomLetter();
}

bool check = false;
void pickRandomLetter() {
  if (learning) {
    randomIndex++;
    if ((randomIndex > 25) || check) {
      check = true;
      randomIndex = random(0, alphaSize);
    }
  } else {
    randomIndex = random(0, alphaSize);
  }
  
  currentLetter = alphaProp[randomIndex];
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Morse for letter: ");
  lcd.setCursor(0,1);
  lcd.print(currentLetter.letter);
  if (learning) {
    showLetter();
  }
}

void showLetter() {

  for (int i = 0; i < currentLetter.morseCode.length(); i++) {
    if (currentLetter.morseCode[i] == '0') {
      tone(buzzer, 783, 500);
      digitalWrite(LEDSB, HIGH);
      delay(500);
      digitalWrite(LEDSB, LOW);
      delay(100);
    } else if (currentLetter.morseCode[i] == '1') {
      tone(buzzer, 783, 1000);
      digitalWrite(LEDLB, HIGH);
      delay(1000);
      digitalWrite(LEDLB, LOW);
      delay(100);
    }
  }
}

void morseCheck() {

  if (buttonLog == alphaProp[randomIndex].morseCode) {
    congrats();
    Serial.println(alphaProp[randomIndex].letter);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Great Job!");
    delay(7000);
  } else {
    lost();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Incorrect Input");
    lcd.setCursor(0,1);
    lcd.print(":\(");
    delay(7000);
    //player.stop();
  }

  buttonLog = "";
}

void loop() {

  if (sb_pressed) {
    tone(buzzer, 783, 500);
    digitalWrite(LEDSB, HIGH);
    buttonLog += "0"; 
    delay(500);
    digitalWrite(LEDSB, LOW);
    sb_pressed = false;
  }

  if (lb_pressed) {
    tone(buzzer, 783, 1000);
    digitalWrite(LEDLB, HIGH);
    buttonLog += "1";
    delay(1000);
    digitalWrite(LEDLB, LOW);
    lb_pressed = false;
  }

  if (stop_pressed) {
    digitalWrite(LEDSE, HIGH);
    delay(500);
    digitalWrite(LEDSE, LOW);
    morseCheck();
    stop_pressed = false;

    pickRandomLetter();
  }
}