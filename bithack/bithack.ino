const int shortButton = 7;
const int longButton;
const int startEnd;
const int LEDSB = 15;
const int LEDLB;
const int LEDSE;

//turns on the green led for 1s when the short Button is pressed
void short_light() {
  digitalWrite(LEDSB, HIGH);
  delay(1000);
  digitalWrite(LEDSB, LOW);
}

void setup() {
  pinMode(shortButton, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:

}
