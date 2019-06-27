#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>

#define Kitchen 14  //DGPI014 D5 
#define HallLight 12  // DGPI012 D6 
#define HallFan 13  // DGPI013 D7

#include "DHT.h"
#define DHTPIN 2  // what pin we're connected to D4
#define DHTTYPE DHT22  // DHT 22  (AM2302)
#define geyser 5 //D1
#define VTemp 4

int minTemp1 = 29;
int minTemp2 = 60;

DHT dht(DHTPIN, DHTTYPE);
float temp_c;

// WiFi network info.
char ssid[] = "Honor 6X";
char wifiPassword[] = "90909090";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "c74bc070-4618-11e8-9c3e-8331599aadae";
char password[] = "395d3d4a8523fbdec9dbe69c2ac93281d03c9983";
char clientID[] = "87463d90-576d-11e9-96ab-dbf3f71adc2a";


void setup() {
//   pinMode(fan, OUTPUT);
  pinMode(geyser, OUTPUT);
  Serial.begin(9600); 
  dht.begin();
  
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
 
   pinMode(HallLight, OUTPUT);        //Hall
 // digitalWrite(Hall, HIGH);
  pinMode(HallFan, OUTPUT);        //room
 // digitalWrite(15, LOW);
  pinMode(Kitchen, OUTPUT);        //kitchen
 // digitalWrite(, LOW);

}

void loop() {
  Cayenne.loop();

  delay(2000);
  float t = dht.readTemperature();
    
  if( t < minTemp1) {
      digitalWrite(geyser, HIGH);
  } 
  if( t >= minTemp2){
     digitalWrite(geyser, LOW); 
  }
  
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");

  Cayenne.virtualWrite(VTemp, t);
}

CAYENNE_OUT_DEFAULT()
{
  Cayenne.virtualWrite(0, millis());
}

CAYENNE_IN(5)
{
  int currentValue1 = getValue.asInt();
  if (currentValue1 == 1)
  {    
    digitalWrite(Kitchen, HIGH);
    Serial.print("Kitchen On");
   }
   else if(currentValue1 == 0)
   {
    digitalWrite(Kitchen, LOW);
    Serial.print("Kitchen Off");
   }
} 
         
CAYENNE_IN(6)
{
  int currentValue3 = getValue.asInt();
  if (currentValue3 == 1)
  {
    digitalWrite(HallLight, HIGH);
    Serial.print("HallLight Off");
  }
  else if(currentValue3 == 0)
  {
    digitalWrite(HallLight, LOW);
   Serial.print("HallLight On");
  }
}
CAYENNE_IN(7)
{
  int currentValue2 = getValue.asInt();
  if (currentValue2 == 1)
  {
    digitalWrite(HallFan, HIGH);
    Serial.print("HallFan On");
  }
  else if(currentValue2 == 0)
  { 
    digitalWrite(HallFan, LOW);
    Serial.print("HallFan Off");
  }
}
        
