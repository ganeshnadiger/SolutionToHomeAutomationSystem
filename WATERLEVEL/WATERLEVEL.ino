#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>

#define WaterLed 0 // D3
const int tank= A0; //sensor pin connected to analog pin A0

float liquid_level;
int liquid_percentage;
int top_level = 512;
int bottom_level = 3;

char ssid[] = "Honor 6X";
char wifiPassword[] = "90909090";

char username[] = "c74bc070-4618-11e8-9c3e-8331599aadae";
char password[] = "395d3d4a8523fbdec9dbe69c2ac93281d03c9983";
char clientID[] = "04818bb0-7718-11e9-beb3-736c9e4bf7d0";

void setup() {
  Serial.begin(115200);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
  pinMode(tank, INPUT);
  pinMode(WaterLed, OUTPUT);
}

void loop() {
  liquid_level = analogRead(tank);
  liquid_percentage = ((liquid_level-bottom_level)/top_level)*100;
  Serial.println(liquid_level);
  Serial.println(liquid_percentage);
  delay(1000);
  Cayenne.loop();
  
  Motor();
}

void Motor(){
  delay(1000);
  if (liquid_percentage < 40.00){
    digitalWrite(WaterLed, HIGH);
  }
  if(liquid_percentage >= 60.00){
    digitalWrite(WaterLed, LOW);
  }
}

CAYENNE_OUT(V10)
{
    Cayenne.virtualWrite(V10, liquid_percentage);
}
