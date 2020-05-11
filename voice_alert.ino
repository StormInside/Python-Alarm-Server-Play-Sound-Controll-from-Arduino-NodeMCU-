#include <ESP8266WiFi.h>

#include <ESP8266HTTPClient.h>

const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

IPAddress ip(192,168,1,52);  
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

int sensorPin=A0;
int val = 0;

int maxVal = 800;

void sendAlert(){
  String address = "http://192.168.1.51:9090/voice_alert";
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
  
void setup(){
  pinMode(sensorPin, INPUT);
  Serial.begin(115200);
  
  // Connect to Wi-Fi
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
 
void loop(){  
  val = analogRead(sensorPin);
 
  if(val>=maxVal){
    Serial.println(WiFi.status() == WL_CONNECTED);
    Serial.println(val);
      sendAlert();
      delay(100);
   }
   delay(10);
}
