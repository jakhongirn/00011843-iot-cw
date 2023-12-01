#define POWER_PIN  13
#define WATER_ANALOG_PIN A0

int waterLevel = 0; // variable to store the sensor value

void setup() {
  Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the water sensor OFF
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the water sensor ON
  delay(10);                      // wait 10 milliseconds
  waterLevel = analogRead(WATER_ANALOG_PIN); // read the analog waterLevel from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  
  // If there is very low level water it should fill some water in the dish
  if (waterLevel < 150) {
    Serial.println("LOW LEVEL WATER!");
  } else {
    Serial.println("Normal water");
  }
  delay(500);
}
