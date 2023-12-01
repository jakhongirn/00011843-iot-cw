#include <Servo.h>

#define TRIG_PIN 9

#define ECHO_PIN 8

Servo servo;

int sound = 250;

bool isFeeding = false;

void setup() {

Serial.begin (9600);

pinMode(TRIG_PIN, OUTPUT);

pinMode(ECHO_PIN, INPUT);

servo.attach(6);


}

void FeedingSystem() {
  long duration, distance;

digitalWrite(TRIG_PIN, LOW);

delayMicroseconds(2);

digitalWrite(TRIG_PIN, HIGH);

delayMicroseconds(10);

digitalWrite(TRIG_PIN, LOW);

duration = pulseIn(ECHO_PIN, HIGH);

distance = (duration/2) / 29.1; if (distance < 30) {

Serial.print(distance);

Serial.println(" cm");

servo.write(90);

}

else if (isFeeding == true) {
  servo.write(90);
}

else {

Serial.println("The distance is more than 30 cm");

servo.write(180); }

delay(500);
}

void loop() {

FeedingSystem();


}