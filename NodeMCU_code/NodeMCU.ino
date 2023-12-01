#include <SoftwareSerial.h>
#include <ArduinoJson.h> // WARNING: ArduinoJson5 here. Latest ArduinoJson6 has a different syntax.

// Creating a software serial to communicate between Arduino and NodeMCU
// Here pin D1 is TX and pin D2 is RX
// Connect the RX pin of Arduino to TX of NodeMCU and TX of Arduino to RX of NodeMCU
SoftwareSerial espSerial(D1, D2);

void setup() 
{
  // Starting the serial in 115200 baud. (Keep the baud rate same everywhere!)
  Serial.begin(115200);
  espSerial.begin(115200);
}

void loop() {
  
  // Creating a JsonBuffer with the same size and reading the data
  // This syntax is a bit different in ArduinoJson6
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(espSerial);
  
  // Using the data read from Arduino
  float h = data["hum"];
  float t = data["temp"];
  
  //Printing the data
  Serial.println("Humidity: " + String(h));
  Serial.println("Temperature: " + String(t));
  
  delay(2000);
}