const int shortButton = 6;
const int longButton = 7;
//const int startEnd;
const int LEDSB = 5;
const int LEDLB = 4;
//const int LEDSE;
int startCountDown = 0;
int count = 0;

//turns on the green led for 1s when the short Button is pressed
void short_light() {
  /*count++;
  Serial.write("activated\n");

  if (count%2 == 0) {
    digitalWrite(LEDSB, LOW);
  } else {
    digitalWrite(LEDSB, HIGH);
  }*/

  int shortLightCountDown = 1000;
  while(shortLightCountDown > 0){
    shortLightCountDown--;
    digitalWrite(LEDSB, HIGH);
  }
  digitalWrite(LEDSB, LOW);
}

void long_light(){
  int longLightCountDown = 3000;
  while(longLightCountDown > 0){
    longLightCountDown--;
    digitalWrite(LEDLB, HIGH);
  }
  digitalWrite(LEDLB, LOW);
}

void setup() {
  pinMode(shortButton, INPUT_PULLUP);
  pinMode(LEDSB, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(shortButton), short_light, FALLING);
  attachInterrupt(digitalPinToInterrupt(longButton), long_light, FALLING);

  Serial.begin(115200);

}


void loop() {

  /*if(startCountDown && longLightCount > 0){
    longLightCount--;
    digitalWrite(LEDLB, HIGH);
  }else{
    digitalWrite(LEDLB, LOW);
    startCountDown = 0;
  }*/
}
