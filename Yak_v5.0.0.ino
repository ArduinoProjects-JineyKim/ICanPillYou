#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
//#include <Servo.h>
#include <time.h>

#define FIREBASE_HOST "icanpillyou-c06f8-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "5NQ7aE98fnXUbVlmICjiymzInX0chrsFgiDCNt0O"
#define WIFI_SSID "ssidName"
#define WIFI_PASSWORD "password"

//#define gidoongMin 180
//#define gidoongMax 100
//#define pusherMin 0
//#define pusherMax 80

FirebaseData firebaseData;
FirebaseJson json;

WiFiServer server(80);

//Servo Yak1gidoong;
//Servo Yak1pusher;
//Servo Yak2gidoong;
//Servo Yak2pusher;

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

//void Abet(){
//  betSucc=0;
//  while(betSucc==0){
//    for(int i=0;i<5;i++){
//      Yak1gidoong.write(150);
//      delay(100);
//      Yak1gidoong.write(gidoongMin);
//      delay(100);
//    }
//    delay(400);
//    for(int i=gidoongMin;i>gidoongMax;i--){
//      Yak1gidoong.write(i);
//      delay(20);
//    }
//    delay(100);
//    for(int i=pusherMin;i<pusherMax;i++){
//      Yak1pusher.write(i);
//      delay(5);
//    }
//    for(int i=0;i<500;i++){
//      if(i==499)break;
//      if(digitalRead(5)==0){
//        betSucc=1;
//        break;
//      }
//      delay(1);
//    }
//    for(int i=pusherMax;i>pusherMin;i--){
//      Yak1pusher.write(i);
//      delay(5);
//    }
//  }
//  Yak1gidoong.write(180);
//}
//
//void Bbet(){
//  betSucc=0;
//  while(betSucc==0){
//    for(int i=0;i<5;i++){
//      Yak2gidoong.write(150);
//      delay(100);
//      Yak2gidoong.write(gidoongMin);
//      delay(100);
//    }
//    delay(400);
//    for(int i=gidoongMin;i>gidoongMax;i--){
//      Yak2gidoong.write(i);
//      delay(20);
//    }
//    delay(100);
//    for(int i=pusherMin;i<pusherMax;i++){
//      Yak2pusher.write(i);
//      delay(5);
//    }
//    for(int i=0;i<500;i++){
//      if(i==499)break;
//      if(digitalRead(2)==0){
//        betSucc=1;
//        break;
//      }
//      delay(1);
//    }
//    for(int i=pusherMax;i>pusherMin;i--){
//      Yak2pusher.write(i);
//      delay(5);
//    }
//  }
//  Yak2gidoong.write(180);
//}

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

void setup()
{
  Serial.begin(115200);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
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
//
//  Yak1gidoong.attach(4);
//  Yak1pusher.attach(14);
//  Yak2gidoong.attach(12);
//  Yak2pusher.attach(15);
//  Yak1gidoong.write(180);
//  Yak1pusher.write(0);
//  Yak2gidoong.write(180);
//  Yak2pusher.write(0);
}
 
void loop()
{
  int flag=0;
  rtcTime();
  dbTime();
//  if (Firebase.getString(firebaseData, "Manual/dispenser_A")){
//      manual_A = firebaseData.stringData();
//  }
//  if (Firebase.getString(firebaseData, "Manual/dispenser_B")){
//      manual_B = firebaseData.stringData();
//  }
//  while(manual_A[0]==116){
//    if(manual_B[0]==116){
//      Serial.print("3");
//    }else{
//      Serial.print("1");
//    }
//    delay(10000);
//    Firebase.getString(firebaseData, "Manual/dispenser_A");
//    manual_A = firebaseData.stringData();
//    Firebase.getString(firebaseData, "Manual/dispenser_B");
//    manual_B = firebaseData.stringData();
//  }
//  while(manual_B[0]==116){
//    if(manual_A[0]==116){
//      Serial.print("3");
//    }else{
//      Serial.print("2");
//    }
//    delay(10000);
//    Firebase.getString(firebaseData, "Manual/dispenser_A");
//    manual_A = firebaseData.stringData();
//    Firebase.getString(firebaseData, "Manual/dispenser_B");
//    manual_B = firebaseData.stringData();
//  }
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
//  Serial.print(dbHour);
//  Serial.print(dbMini);
//  Serial.print(" ");
//  Serial.print(rtcHour);
//  Serial.print(rtcMini);
//  Serial.print("\n");
  delay(100);
}
