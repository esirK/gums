/*
  Connect ESP32 to gums servers
 * Description:  connects to gums API using an ESP32 Wifi module.
 */
 
#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient ask;

const char* ssid = "Jibambex";//Wifi SSID
const char* password = "13333334";//Wifi Password

// GUMS API host config
const char* host = "192.168.100.80";  // API host name
const int httpPort = 8080;     // port

// Use WiFiClient class to create TCP connections
WiFiClient client;

void setup(){

  // open serial
  Serial.begin(115200);
  Serial.println("*****************************************************");
  Serial.println("********** Program Start : Connect GUMS to GUMS server");
  Serial.println("Wait for WiFi... ");

  // connecting to the WiFi network
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // connected
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop(){
  if (!client.connect(host, httpPort)){
    Serial.println("connection to");
    Serial.println(host);
    Serial.println("failed.");
    delay(10000);
    return;
  }
  String url = "http://192.168.100.80:8080/";
  Serial.print("********** requesting URL: ");
  Serial.println(url);

  ask.begin(url);

  int httpResponseCode = ask.GET();

  String payload = ask.getString();
  Serial.println(httpResponseCode);
  Serial.println(payload);

  ask.end();
  client.stop();
  delay(10000);
}
