<h1>Terra Firma</h1>

Terra Firma is a small project made during a four hour competition. It is related to agriculture and remote monitoring using a couple of sensors.

Components Required:

BreadBoard - Half Size

NodeMCU (ESP8266 12E)

LDR Sensor

Temperature + Humidity Sensors (DHT11/DHT22)

10K Ohm Resistor X 2

Circuit Diagram:

![alt text](https://github.com/tanujthakkar/Terra-Firma/blob/master/Terra%20Frima%20Circuit.png)

Firebase Setup:
1. Make a new Firebase project
2. Go to database and create a Realtime Database in locked mode
3. Copy the database URL [example - "yourproject.firebaseio.com"] (to be used in NodeMCU code)
4. Add "humidity", "temperature", and "light" to the database with values set to 0
5. Switch to the rules tab and change read and write to "true"
6. Open Project Settings and switch to Service Accounts, select Databse Secrets and copy your database secret (to be used in NodeMCU code)

NodeMCU Setup:
1. Construct the circuit shown in the circuit diagram
2. Open the code file "auction.ino" in the ESP8266 folder.
3. Fill in your WiFi details in "Setting up ESP8266 libraries and WiFi" section
4. Fill in your Firebase details in "Setting up Firebase with mandatory details". The database URL goes to FIREBASE_HOST and the database secret goes to FIREBASE_AUTH.
5. Upload the code.
NOTE: If you're having a problem with the Firebase library, open the library folder, open "FirebaseHttpClient.h" in src folder and change the "kFirebaseFingerPrint" to "E2 34 53 7A 1E D9 7D B8 C5 02 36 0D B2 77 9E 5E 0F 32 71 17". (Active fingerprint at the time this was written)

Android Setup:
1. Open the project
2. Find Firebase under tools
3. Select "Save and Retrieve" under Realtime Database
4. Login to your Google Account and select your Firebase Project.

NOTE: Don't change the project dependencies, that'll result in a newer version which doesn't work.
