#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(9600);
  dht.begin(); // initialize the sensor

  // initialize digital pins as outputs.
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  
  // check if any reads failed
  if (isnan(humi) || isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.println("%");

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.println("°C");
  }

  if (tempC >= 30) {
    digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
    analogWrite(ENA_PIN, 100); // control the speed
  }
  else {
    digitalWrite(IN1_PIN, LOW);
  }
  
  delay(1000); 
}
