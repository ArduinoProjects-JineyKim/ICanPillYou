#include <ESP8266WiFi.h>
#include <Servo.h>
#include <time.h>
 
const char* ssid = "sugosugo";
const char* password = "qwertyui12";
char curTime[20];  
WiFiServer server(80);
Servo Yak1;
Servo Yak2;

bool a;
 
void setup(){
  Serial.begin(115200);
  delay(10);

  pinMode(2, OUTPUT);
  digitalWrite(2, 0);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  server.begin();
  Serial.println("Server started");

  Serial.println(WiFi.localIP());
  
  configTime(9*3600, 0, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) delay(500);
  Yak1.attach(4,544,2400);
  Yak2.attach(14,544,2400);
  Yak1.write(90);
  Yak2.write(90);
}
 
void loop() {
  time_t now = time(nullptr);
  struct tm *t;
  t = localtime(&now);
 
  sprintf(curTime,"%04d-%02d-%02d %02d:%02d:%02d", t->tm_year+1900, t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
  Serial.println(curTime);
//  if((t->tm_hour==18&&t->tm_min==48)&&t->tm_sec==30)
//  {
//    Serial.println("약먹어");
//  }
  Yak1.write(((t->tm_sec)*12)%180);
  if((t->tm_sec)%2==0){
    Yak2.write(180);
  }else{
    Yak2.write(0);
  }
  
  delay(10);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of he request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  digitalWrite(2, val);
  
  client.flush();

  // Prepare the response
  int sensorReading = analogRead(A0);
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>GPIO2 is now = ";
  s += (val)?"high<p>":"low<p>";
  s += "Analog Value is now = ";
  s += (sensorReading);
  s += "</h1><p>";
  s += "<img src='https://lh4.ggpht.com/yPq0eEBNR4g530UHDfpbtwe-yiAMLVjUcnGCsjW9_K9VniuLr_YbeefSsd3uqYvZWJ8=w300'><p>";
  s += "<iframe width='560' height='315' src='https://www.youtube.com/embed/ZicP4y-nFg4' frameborder='0' allowfullscreen></iframe>";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
}
