/**
 * Example for reading temperature and humidity
 * using the DHT22 and ESP8266 (NodeMcu)
 */

#include "DHT.h"

// Sometimes the baud rate can be different of other boards
#define BAUD 9600
#define BAUD_NODEMCU 115200
// digital pin the DHT22 is conected to (DHTPIN 4 maps to D2 on NodeMcu)
#define DHTPIN 4
// Since there are multiple kinds of DHT sensors
#define DHTTYPE DHT22

// DHT sensor initislization
DHT dht(DHTPIN, DHTTYPE);

//---Variables---
// Reporting time in milliseconds
int reportingTime = 10000;
//Stores humidity value
float hum;
//Stores temperature value in Celcius  
float tempInC;
//Stores temperature value in Celcius  
float tempInF;
// Stores heatindex in C
float heatIndexC;
// Stores heatindex in F
float heatIndexF;

void setup() {
  Serial.begin(BAUD_NODEMCU);
  //Serial.setTimeout(4000);
  delay(1000);

  Serial.println("\n");
  Serial.println("Setup");

  // Wait for serial to initialize.
  while(!Serial) { }

  Serial.println("Device Started");
  Serial.println("-------------------------------------");
  Serial.println("Running DHT!");
  Serial.println("-------------------------------------");
}

int timeSinceLastRead = 0;
void loop() {

  // Report every n seconds
  if(timeSinceLastRead > reportingTime) {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float hum = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float tempInC = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float tempInF = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(hum) || isnan(tempInC) || isnan(tempInF)) {
      Serial.println("Failed to read from DHT sensor!");
      timeSinceLastRead = 0;
      return;
    }

    // Compute heat index in Fahrenheit (the default)
    heatIndexF = dht.computeHeatIndex(tempInF, hum);
    // Compute heat index in Celsius (isFahreheit = false)
    heatIndexC = dht.computeHeatIndex(tempInC, hum, false);

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(tempInC);
    Serial.print(" *C ");
    Serial.print(tempInF);
    Serial.print(" *F\t");
    Serial.print("Heat index: ");
    Serial.print(heatIndexC);
    Serial.print(" *C ");
    Serial.print(heatIndexF);
    Serial.println(" *F");

    timeSinceLastRead = 0;
  }
  delay(100);
  timeSinceLastRead += 100;
}
