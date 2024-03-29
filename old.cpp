/*
  Connect ESP32 to gums servers
 * Description:  connects to gums API using an ESP32 Wifi module.
 */
 
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti WiFiMulti;
HTTPClient ask;
// TODO: user config
const char* ssid     = "............."; //Wifi SSID
const char* password = "............."; //Wifi Password
const char* apiKeyIn = "...................";      // API KEY IN
const unsigned int writeInterval = 25000;   // write interval (in ms)

// ASKSENSORS API host config
const char* host = "api.asksensors.com";  // API host name
const int httpPort = 80;      // port
  
void setup(){
  
  // open serial
  Serial.begin(115200);
  Serial.println("*****************************************************");
  Serial.println("********** Program Start : Connect ESP32 to AskSensors.");
  Serial.println("Wait for WiFi... ");

  // connecting to the WiFi network
  WiFiMulti.addAP(ssid, password);
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // connected
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop(){

  // Use WiFiClient class to create TCP connections
  WiFiClient client;


  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }else {

    // Create a URL for updating module1 and module 2
  String url = "http://api.asksensors.com/write/";
  url += apiKeyIn;
  url += "?module1=";
  url += random(10, 100);
  url += "&module2=";
  url += random(10, 100);
    
  Serial.print("********** requesting URL: ");
  Serial.println(url);
   // send data 
   ask.begin(url); //Specify the URL
  
    //Check for the returning code
    int httpCode = ask.GET();          
 
    if (httpCode > 0) { 
 
        String payload = ask.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      } else {
      Serial.println("Error on HTTP request");
    }
 
    ask.end(); //End 
    Serial.println("********** End ");
    Serial.println("*****************************************************");

  }

  client.stop();  // stop client
  
  delay(writeInterval);    // delay
}
