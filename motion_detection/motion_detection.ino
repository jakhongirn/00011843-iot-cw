const int motionpin = A0;
const int ledpin = 13;
const int buzzpin = 12;  // ledpin, motionpin and buzpin are not changed throughout the process
int motionsensvalue = 0;

const bool isMotionDetectorMode = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  pinMode(motionpin, INPUT);
  pinMode(buzzpin, OUTPUT);
}


void sirenSound() {           //This function produces the 4th siren(POLICE) sound with led transition.
digitalWrite(ledpin, HIGH);
for(int i=3;i<=11;i+=2)
digitalWrite(i,HIGH);
  for(int hz = 440; hz < 1000; hz++){
    tone(buzzpin, hz, 50);
    delay(5);
  }

for(int i=3;i<=11;i+=2)
digitalWrite(i,LOW);
 for(int i=4;i<=12;i+=2)
digitalWrite(i,HIGH);
  for(int hz = 1000; hz > 440; hz--){
    tone(buzzpin, hz, 50);
    delay(5);
    }

digitalWrite(ledpin, LOW);
}




void motionDetection() {
  motionsensvalue = analogRead(motionpin);  // reads analog data from motion sensor

  Serial.println(motionsensvalue);
  if (motionsensvalue >= 200) {
    digitalWrite(ledpin, HIGH);
    sirenSound();  //turns on led and buzzer
  } else {
    digitalWrite(ledpin, LOW);  //turns led off led and buzzer
    noTone(buzzpin);
  }
}

void loop() {
  if (isMotionDetectorMode == true) {
    motionDetection();
    delay(1000);
  }
  
}