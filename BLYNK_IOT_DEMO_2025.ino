#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3nSKfXSlY"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "owFRW_CR549heGBwrMnDEYqvFT-OCmKW"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

int DHTTYPE = DHT11;      // DHT 11
int pin = 2;              // Digital pin 2

DHT dht(pin, DHTTYPE);  // Class & Object Creation

BlynkTimer timer;

char ssid[] = "SIT";
char pass[] = "SIT@1234";

int value1,value2;
float t,h;

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();

  pinMode(D0,OUTPUT);   // LED 1 i.e. GPIO 16
  pinMode(D3,OUTPUT);   // LED 2 i.e. GPIO 0

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000, aapala_function);
}

void loop()
{
  Blynk.run();
  timer.run();
}

BLYNK_WRITE(V0)      // LAMP 1
{
  value1 = param.asInt();
  digitalWrite(D0,value1);
}

BLYNK_WRITE(V1)      // LAMP 2
{
  value2 = param.asInt();
  digitalWrite(D3,value2);
}

void aapala_function()
{
  h = dht.readHumidity();
  t = dht.readTemperature(); 
  
  Serial.println("Temp = "+String(t)+" *C \t Humi ="+String(h)+" %");
  
  Blynk.virtualWrite(V4,t);
  Blynk.virtualWrite(V5,h);
}



