#include<ESP8266WiFi.h>
#include<WiFiClient.h>


const char*ssid = "Thar Htet Aung";
const char*password = "tharhtetaung524123";

void setup() 
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    delay(1000);
    Serial.println();
    Serial.println("Setting Access Point");

    WiFi.begin(ssid,password);
    while(WiFi.status()!= WL_CONNECTED)
    {
        Serial.println(".");
        delay(500);
    }
      Serial.println(" ");
      Serial.println("Connected WiFi Network!");
      Serial.println("Host Address is..");
      Serial.println(WiFi.localIP());
      
}

void loop() {
  // put your main code here, to run repeatedly:

}
