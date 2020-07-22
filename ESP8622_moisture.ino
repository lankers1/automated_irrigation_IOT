#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>

const String sensorName = "***"; //Identifier of sensor
const String ssid = "***"; //Name for Wi-Fi network
const String password = "***"; //Password for Wi-Fi network
const char* host = "***"; //IP address of raspberry pi
const int port = 3000;

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }
}

void loop() {
    Serial.println(analogRead(A0));    
    float delta = 1024 - 670;
    float val = analogRead(A0) - 670;
    float level = val / delta * 100;
    
    postData(level);    
    delay(1000);
}

void postData(float data) {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin("http://" + (String)host + ":" + (String)port + "/measurement/" + (String)sensorName);
    http.addHeader("Content-Type", "application/json");
    http.POST("{\"capacity\": \"" + (String)data + "\"}");
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}