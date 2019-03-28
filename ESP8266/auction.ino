// Setting up ESP8266 libraries and WiFi
#include <ESP8266WiFi.h>
#define WIFI_SSID "Your WiFi SSID"
#define WIFI_PASSWORD "Your WiFi Password"
#define WIFI_LED BUILTIN_LED

// Setting up DHT sensor dependencies, pin and object variables
#include "DHT.h"
#define DHT_PIN_DATA 5
DHT dht(DHT_PIN_DATA);

// Setting up Firebase with mandatory details
#include <FirebaseArduino.h>
#define FIREBASE_HOST "Your database URL"
#define FIREBASE_AUTH "Your database secret"

// Sensor Data Variables
float humidity;
float temperature;
int ldr;

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

  // Initializing DHT sensor
  dht.begin();

  // Initializing Firebase connection
  Firebase.begin(FIREBASE_HOST);  
}

void loop() {

  humidity = dht.readHumidity();    // Retrieving humidity data
  temperature = dht.readTempC();    // Retrieving temperature data

  Firebase.setInt("/humidity", int(humidity));    // Updating humidity data to Firebase
  Firebase.setInt("/temperature", int(temperature));    // Updating temperature data to Firebase

  ldr = analogRead(A0);   // Retrieving LDR data
  ldr = map(ldr, 0, 1023, 0, 100);
  if(ldr >= 70) {
    digitalWrite(D2, LOW);
  } else {
    digitalWrite(D2, HIGH);
  }
  Firebase.setInt("/light", ldr);   // Updating LDR data to Firebase
}
