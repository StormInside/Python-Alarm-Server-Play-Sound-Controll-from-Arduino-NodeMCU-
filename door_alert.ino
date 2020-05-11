#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

IPAddress ip(192,168,1,53);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

const int input = 5;
const int light = 4;
const int light2 = 14;

void sendAlert(){
  String address = "http://192.168.1.51:9090/door_alert";
  WiFiClient client;
  HTTPClient http;
  if(WiFi.status() == WL_CONNECTED){
    http.begin(address);
    int httpCode = http.GET();
    Serial.println(httpCode);
    http.end();
  }else{
    Serial.println("no wifi");
  }
}

void setup() {
  pinMode(input, INPUT);
  pinMode(light, OUTPUT);
  pinMode(light2, OUTPUT);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }

  // Print ESP8266 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(light, LOW);
  if(WiFi.status()== WL_CONNECTED){
    digitalWrite(light2, HIGH);
  }else{
    Serial.println("No WiFi");
    digitalWrite(light2, LOW);
  }
  if(digitalRead(input)!=1){
    Serial.println("Field detected, sending ALERT!!!");
    digitalWrite(light, HIGH);
    sendAlert();
    delay(1000);
  }
//  delay(10);
}
