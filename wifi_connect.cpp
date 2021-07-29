#include <ESP8266WiFi.h>
#include <String.h>

String ssid = "";
String password = "";

void setup()
{
  Serial.begin(9600);
  Serial.println();
}

void loop() 
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("SSID: ");
    while (Serial.available()==0)
    {
      
    }
    ssid = Serial.readString();
    Serial.println();
    Serial.print("Password: ");
    while (Serial.available()==0)
    {

    }
    password = Serial.readString();
  }
  Serial.print(ssid);
  Serial.println();
  Serial.print(password);
  Serial.println();
}