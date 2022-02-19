#include <ESP8266WiFi.h>                                                // esp8266 library
#include "FirebaseArduino.h"                                            // firebase library

#define FIREBASE_HOST "icanpillyou-c06f8.firebaseapp.com/"                         // the project name address from firebase id
#define FIREBASE_AUTH "AIzaSyBh92t7El2QKWz1RO-_PjKKE654dyWogaE"                    // the secret key generated from firebase
#define WIFI_SSID "sugosugo"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "qwertyui 12"                                    //password of wifi ssid

FirebaseData yakData;
FirebaseJson json;

void setup()
{
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  Serial.println(yakData.dataPath());
  delay(500);
}
