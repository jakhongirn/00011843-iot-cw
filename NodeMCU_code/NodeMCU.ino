#include <SoftwareSerial.h>
#include <ArduinoJson.h> // WARNING: ArduinoJson5 here. Latest ArduinoJson6 has a different syntax.
#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>

// Creating a software serial to communicate between Arduino and NodeMCU
// Here pin D1 is TX and pin D2 is RX
// Connect the RX pin of Arduino to TX of NodeMCU and TX of Arduino to RX of NodeMCU
SoftwareSerial espSerial(D1, D2);

#define FIREBASE_HOST "https://iot-pro-a1acb-default-rtdb.firebaseio.com/"
#define WIFI_SSID "Miphone" // Change the name of your WIFI
#define WIFI_PASSWORD "12345678qwe" // Change the password of your WIFI
#define FIREBASE_Authorization_key "AIzaSyDXXxFL03802VQC9onjWHIhcq1BZNwgxKM"


FirebaseData firebaseData;
FirebaseJson json;

void setup() 
{
  // Starting the serial in 115200 baud. (Keep the baud rate same everywhere!)
  Serial.begin(115200);
  espSerial.begin(115200);

  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
}

void loop() {

  
  // Creating a JsonBuffer with the same size and reading the data
  // This syntax is a bit different in ArduinoJson6
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(espSerial);
  
  // Using the data read from Arduino
  float humid = data["hum"];
  float temp = data["temp"];
  
  //Sending data to firebase
  Firebase.setFloat(firebaseData, "/temp", temp);
  Firebase.setFloat(firebaseData, "/humid", humid);

  //Printing the data
  Serial.println("Humidity: " + String(h));
  Serial.println("Temperature: " + String(t));
  


  delay(2000);
}