/* Use a photoresistor (or photocell) to turn on an LED in the dark
   More info and circuit schematic: http://www.ardumotive.com/how-to-use-a-photoresistor-en.html
   Dev: Michalis Vasilakis // Date: 8/6/2015 // www.ardumotive.com */
   

//Constants
const int PHOTO_RES_PIN = A0; // Photoresistor at Arduino analog pin A0
const int LIGHT_LED_PIN=13;       // Led pin at Arduino pin 9

//Variables
int photoResValue;				  // Store value from photoresistor (0-1023)

void setup(){
Serial.begin(9600);
 pinMode(LIGHT_LED_PIN, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(PHOTO_RES_PIN, INPUT);// Set PHOTO_RES_PIN - A0 pin as an input (optional)
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

void loop(){
  LightControl();
}