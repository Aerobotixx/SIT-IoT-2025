#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

String ssid = "SIT";
String password = "SIT@1234";

ESP8266WebServer server(80);      //http port number is 80

void setup()
{
  Serial.begin(9600);   // Default BAUD Rate of Serial Communication (RS232)
  Serial.print("Connecting to : ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);     //Connect to your WiFi router
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");    // Wait until server gets connected to your Wi-Fi network
  }
  Serial.print("Connected Sueccessfully...!!! ");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your server 
  server.begin();  

  // Run your custom funtion
  server.on("/", maziwebsite);      //Which routine to handle at root location
                
}

void loop()
{
  server.handleClient();          //Handle client requests
}

void maziwebsite()
{
  server.send(200, "text/plain", "hi... My name is ESP8266");   // Response from server
}
