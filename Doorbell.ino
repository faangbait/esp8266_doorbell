#include <ESP8266WiFi.h>

const char* ssid     = "208C";
const char* password = "";

const char* url = "/trigger/doorbell/with/key/privatekeyhere";

const int buttonPin=2;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin,INPUT);
}

int value = 0;

void loop() {
  checkWifi();
  
  if (digitalRead(buttonPIN)==LOW)
  {
    dingdong();
    delay(2000);
  }

}

void checkWifi(){
  if ((WiFi.status() != WL_CONNECTED)) {
    WiFi.disconnect();
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid,password);
    delay(6000);
  }
}

void dingdong(){
  Serial.println("Ringing doorbell...");
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect("maker.ifttt.com", httpPort)) {
    Serial.println("connection failed");
    return;
  }
  client.println(String("GET ") + url + " HTTP/1.1");
  client.println("Host: maker.ifttt.com");
  client.println("Connection: close");
  client.println();
  
  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
}

