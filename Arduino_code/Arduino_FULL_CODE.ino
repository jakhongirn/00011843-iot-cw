#include <SoftwareSerial.h>
#include <ArduinoJson.h> // WARNING: ArduinoJson5 here. Latest ArduinoJson6 has a different syntax.
#include "DHT.h"
#include <Servo.h>

// Creating a software serial to communicate between Arduino and NodeMCU
// Here pin 10 is TX and pin 11 is RX
SoftwareSerial espSerial(10, 11);


//Temperature and Humidity pins
#define DHTPIN 13
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); // inherit temp&humid class
const int ENA_PIN = 12; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 9; // the Arduino pin connected to the IN1 pin L298N


// Water sensor pins
#define WATER_PIN  5
#define WATER_ANALOG_PIN A4
const int WATER_PUMP_PIN = 3;
int waterLevel = 0; // initialize the water level variable


// Ultrasonic Sensor pins
#define TRIG_PIN 8
#define ECHO_PIN 7
Servo servo; // inherit servo class
int sound = 250;


//Photoresistor pins 
const int PHOTO_RES_PIN = A3; // Photoresistor at Arduino analog pin A0
const int LIGHT_LED_PIN= 4;   // Led pin at Arduino pin 9
int photoResValue;			


//Motion sensor pins
const int MOTION_PIN = A1;
const int LED_PIN = 13;
const int BUZZ_PIN = 12;  // LED_PIN, MOTION_PIN and buzpin are not changed throughout the process
int motionsensvalue = 0;


void setup()
{
  dht.begin();
  // Starting the serial both in 115200 baud. (Both baud rate has to be same)
  Serial.begin(115200);
  espSerial.begin(115200);

  //configuring L298N digital pins 
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  

  //configuring water pins
  pinMode(WATER_PIN, OUTPUT);   
  digitalWrite(WATER_PIN, LOW); 
  pinMode(WATER_PUMP_PIN, OUTPUT);


  //configuring ultrasonic servo pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(2);

  //configuring Photoresistor pins
  pinMode(LIGHT_LED_PIN, OUTPUT); 
  pinMode(PHOTO_RES_PIN, INPUT);

  //configuring Motion sensor pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTION_PIN, INPUT);
  pinMode(BUZZ_PIN, OUTPUT);

}


void ControlFAN(int tempC) {
  if (tempC >= 30) {
    digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
    analogWrite(ENA_PIN, 100); // control the speed with 100 value
  }
  else {
    digitalWrite(IN1_PIN, LOW);
  }
}


void FeedingSystem(bool isFeeding) {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1; 

  if (distance < 30) {
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

void LightControl(){
  photoResValue = analogRead(PHOTO_RES_PIN);
  
  Serial.println(photoResValue);
  //You can change photoResValue "25"
  if (photoResValue > 10){
    digitalWrite(LIGHT_LED_PIN, LOW);  //Turn led off
  }
  else{
    digitalWrite(LIGHT_LED_PIN, HIGH); //Turn led on
  }

  delay(500); //Small delay
}

void motionDetection(bool isMotionDetectorMode) {
  motionsensvalue = analogRead(MOTION_PIN);  // reads analog data from motion sensor

  Serial.println(motionsensvalue);
  if (motionsensvalue >= 200) {
    digitalWrite(LED_PIN, HIGH);
    sirenSound();  //turns on led and buzzer
  } else {
    digitalWrite(LED_PIN, LOW);  //turns led off led and buzzer
    noTone(BUZZ_PIN);
  }
}


void sirenSound() {           //This function produces the siren(POLICE) sound with led transition.
  digitalWrite(LED_PIN, HIGH);
  for(int i=3;i<=11;i+=2)
  digitalWrite(i,HIGH);
    for(int hz = 440; hz < 1000; hz++){
      tone(BUZZ_PIN, hz, 50);
      delay(5);
    }

  for(int i=3;i<=11;i+=2)
  digitalWrite(i,LOW);
  for(int i=4;i<=12;i+=2)
  digitalWrite(i,HIGH);
    for(int hz = 1000; hz > 440; hz--){
      tone(BUZZ_PIN, hz, 50);
      delay(5);
      }

  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  //--------------------Controlling FAN with temperature---------------------
  // Reading temperature and humidity from DHT11
  float humi = dht.readHumidity();
  float tempC = dht.readTemperature();
  ControlFAN(tempC);


  //---------------------Controlling water level----------------------------
  digitalWrite(WATER_PIN, HIGH);  // turn the water sensor ON
  delay(10);                      // wait 10 milliseconds
  waterLevel = analogRead(WATER_ANALOG_PIN); // read the analog waterLevel from sensor
  digitalWrite(WATER_PIN, LOW);   // turn the sensor OFF
  
  // If there is very low level water it should fill some water in the dish
  if (waterLevel < 150) {
    Serial.println("LOW LEVEL WATER!");
    digitalWrite(WATER_PUMP_PIN, HIGH);\
  }
   else if (waterLevel > 600) {
    digitalWrite(WATER_PUMP_PIN, LOW);
   }
   else {
    Serial.println("Normal water");
    
  }

  //----------------------Feeding system------------------------
  bool isFeeding = false;

  FeedingSystem(isFeeding);

  //-----------------------Light Control System---------------------
  LightControl();


  //-------------------------Motion Detection System-----------------------
  bool isMotionDetectorMode = false;

  if (isMotionDetectorMode == true) {
    motionDetection(isMotionDetectorMode);
    delay(1000);
  }

  //-------------------SENDING DATA TO ESP8266----------------------
  // Creating a JsonBuffer with size of 1000 and assigning the json object to a variable
  // This syntax is a bit different in ArduinoJson6 
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();

  // Adding data to the json object
  data["hum"] = humi;
  data["temp"] = tempC;

  // Sending the data to NodeMCU
  data.printTo(espSerial);
  jsonBuffer.clear(); 


  //-------------------SERIAL PRINTING VALUES --------------------------------------
  Serial.println(humi);
  Serial.println(tempC);

  delay(1000);
}


