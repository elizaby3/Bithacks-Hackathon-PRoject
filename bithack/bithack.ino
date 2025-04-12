const int shortButton = 6;
//const int longButton;
//const int startEnd;
const int LEDSB = 5;
//const int LEDLB;
//const int LEDSE;

int count = 0;

//turns on the green led for 1s when the short Button is pressed
void short_light() {
  count++;
  Serial.write("activated\n");

  if (count%2 == 0) {
    digitalWrite(LEDSB, LOW);
  } else {
    digitalWrite(LEDSB, HIGH);
  }
}

void setup() {
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);

  Serial.begin(115200);

}

void loop() {

}

struct Alphabet{ //creates the "dictionary" that allows to access the features of each letter in the alphabet
  String letter;  //accesses the letter
  String morseCode; //accesses the morse code that corresponds to each letter 
  //the morseCode is integers as a string because we'll use the compare function
}

Alphabet alphaProp[] = { //creates an array that includes all letters of the alphabet and its properties as properties 
  {"A", "01"},

}

