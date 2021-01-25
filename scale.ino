/*
  Connect ESP32 to gums servers
 * Description:  connects to gums API using an ESP32 Wifi module.
 */
 
#include <WiFi.h>
#include <HTTPClient.h>

#include "HX711.h"

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define OWNER "0708468333"

#define DOUT  2
#define CLK  15
// VmpKNFUxRnRVWGhoTTJ4WVYwZDRVRlpxUW1GamJGSnlWV3R3VG1GNmJFWldSekZ6VkdzeGMxTnVVbFZpV0VKeFZHdGFjMDVzWkZsaFIwWm9Za1ZaTVZZeGFIZFpWMFpYWTBWb1UxWkVRVGs9
HX711 scale;

HTTPClient http;

const char* ssid = "Jibambex";//Wifi SSID
const char* password = "13333334";//Wifi Password

// GUMS API host config
const char* host = "192.168.100.80";  // API host name
const int httpPort = 8000;     // port

// Use WiFiClient class to create TCP connections
WiFiClient client;

long t;

void setup() {
  Serial.begin(57600);
  delay(10);
  Serial.println();
  Serial.println("Starting...");
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

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 10000; //increase value to slow down serial print activity

  if (millis() > t + serialPrintInterval) {
  String url = "http://192.168.100.80:8000/v1/sensors/";
  Serial.print("********** Sending data to the following URL: ");
  Serial.println(url);
  float i = scale.get_units();
  Serial.print("Load_cell output val: ");
  Serial.println(i);
  http.begin(url);
  
  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "owner=" OWNER "&value1=";
  int httpResponseCode = http.POST(httpRequestData+=i);
  Serial.println(httpResponseCode);
  String payload = http.getString();
  Serial.println(httpResponseCode);
  Serial.println(payload);
  newDataReady = 0;
  t = millis();
  }
}
