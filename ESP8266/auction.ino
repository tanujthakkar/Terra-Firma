#include <ESP8266WiFi.h>
#define WIFI_SSID "Your WiFi SSID"
#define WIFI_PASSWORD "Your WiFi Password"
#define WIFI_LED BUILTIN_LED

#include <FirebaseArduino.h>
#define FIREBASE_HOST "Your database URL"
#define FIREBASE_AUTH "Your database secret"

// Sensor Data Variables
int humidity;
int temperature;
int ldr;

String m;

void setup() {
  
  Serial.begin(9600);

  pinMode(WIFI_LED, OUTPUT);
  pinMode(D2, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  digitalWrite(BUILTIN_LED, HIGH);
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST);  
}

void loop() {

  ldr = analogRead(A0);
  ldr = map(ldr, 0, 1023, 0, 100);
  if(ldr >= 70) {
    digitalWrite(D2, LOW);
  } else {
    digitalWrite(D2, HIGH);
  }
  Firebase.setInt("/light", ldr);
}
