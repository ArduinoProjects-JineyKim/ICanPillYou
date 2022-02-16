#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <time.h>

#define FIREBASE_HOST "icanpillyou-c06f8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5NQ7aE98fnXUbVlmICjiymzInX0chrsFgiDCNt0O"
#define WIFI_SSID "sugosugo"
#define WIFI_PASSWORD "qwertyui12"

FirebaseData firebaseData;
FirebaseJson json;

WiFiServer server(80);

String A_chkbox;
String B_chkbox;
String manual_A;
String manual_B;

int dbHour;
int dbMini;
int rtcHour;
int rtcMini;
int rtcSec;

int betSucc;

void printResult(FirebaseData &data);

void rtcTime(){
  configTime(9*3600, 0, "pool.ntp.org","time.nist.gov");
  while (!time(nullptr)) delay(100);
  time_t now = time(nullptr);
  struct tm *t;
  t = localtime(&now);
  rtcHour=t->tm_hour;
  rtcMini=t->tm_min;
  rtcSec=t->tm_sec;
}

void dbTime(){
  if (Firebase.getString(firebaseData, "Timeset/time")){
    String timedata = firebaseData.stringData();
    dbHour=((timedata[1]-48)*10)+(timedata[2]-48);
    dbMini=((timedata[4]-48)*10)+(timedata[5]-48);
  }
}

void setup(){
  Serial.begin(115200);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
 
void loop(){
  int flag=0;
  rtcTime();
  dbTime();
  if(((dbHour==rtcHour)&&(dbMini==rtcMini))&&((rtcSec>=0)&&(rtcSec<=10))){
    if (Firebase.getString(firebaseData, "Timeset/dispenser_A_chkbox")){
      A_chkbox = firebaseData.stringData();
    }
    if (Firebase.getString(firebaseData, "Timeset/dispenser_B_chkbox")){
      B_chkbox = firebaseData.stringData();
    }
    if((A_chkbox[0]==116)&&(B_chkbox[0]==116)){
      Serial.print("3");
      delay(10000);
    }
    else if(A_chkbox[0]==116){
      Serial.print("1");
      delay(10000);
    }
    else if(B_chkbox[0]==116){
      Serial.print("2");
      delay(10000);
    }
  }else{
    Serial.print("0");
  }
  delay(100);
}
