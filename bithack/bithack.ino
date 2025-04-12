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

void long_light() {
  digitalWrite(LEDLB, HIGH);
  delay(1000);
  digitalWrite(LEDLB, LOW);
}

void setup() {
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);

  Serial.begin(115200);

}

void loop() {

}
