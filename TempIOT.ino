#include "OneWire.h"
#include "DallasTemperature.h"
#include <WiFi.h>
#include "ThingSpeak.h"

OneWire oneWire(2);
DallasTemperature tempSensor(&oneWire);
WiFiClient client;

const char* ssid = "NET_2G2B906E";
const char* password =  "2F2B906E";


unsigned long myChannelNumber = 987506;
const char * myWriteAPIKey = "BHGH8ICCOHEB6O5Z";
void setup(void)
{
  
  Serial.begin(115200);
  tempSensor.begin();
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
}

  
void loop(void)
{
  delay(5000);
  float temperatura = tempSensor.getTempCByIndex(0);
  ThingSpeak.setField(1,temperatura);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  tempSensor.requestTemperaturesByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(tempSensor.getTempCByIndex(0));
  Serial.println(" C");
}
