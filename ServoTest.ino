#include <Servo.h>

#define gidoongMin 180
#define gidoongMax 125
#define pusherMin 0
#define pusherMax 40

Servo Yak1gidoong;
Servo Yak1pusher;
Servo Yak2gidoong;
Servo Yak2pusher;

int betSucc;

void Abet()
{
  betSucc=0;
  while(betSucc==0)
  {
    for(int i=0;i<5;i++)
    {
      Yak1gidoong.write(150);
      delay(100);
      Yak1gidoong.write(180);
      delay(100);
    }
    delay(400);
    for(int i=gidoongMin;i>gidoongMax;i--)
    {
      Yak1gidoong.write(i);
      delay(30);
    }
    delay(100);
    for(int i=pusherMin;i<pusherMax;i++)
    {
      Yak1pusher.write(i);
      delay(10);
    }
    for(int i=0;i<500;i++)
    {
      if(i==499)
      {
        break;
      }
      if(digitalRead(2)==0)
      {
        betSucc=1;
        break;
      }
      delay(1);
    }
    for(int i=pusherMax;i>pusherMin;i--)
    {
      Yak1pusher.write(i);
      delay(10);
    }
  }
  Yak1gidoong.write(180);
}

void Bbet()
{
  betSucc=0;
  while(betSucc==0)
  {
    for(int i=0;i<5;i++)
    {
      Yak2gidoong.write(150);
      delay(100);
      Yak2gidoong.write(180);
      delay(100);
    }
    delay(400);
    for(int i=gidoongMin;i>gidoongMax;i--)
    {
      Yak2gidoong.write(i);
      delay(30);
    }
    delay(100);
    for(int i=pusherMin;i<pusherMax;i++)
    {
      Yak2pusher.write(i);
      delay(10);
    }
    for(int i=0;i<500;i++)
    {
      if(i==499)
      {
        break;
      }
      if(digitalRead(4)==0)
      {
        betSucc=1;
        break;
      }
      delay(1);
    }
    for(int i=pusherMax;i>pusherMin;i--)
    {
      Yak2pusher.write(i);
      delay(10);
    }
  }
  Yak2gidoong.write(180);
}

void setup() 
{
  Serial.begin(115200);
  Yak1gidoong.attach(3);
  Yak1pusher.attach(5);
  Yak2gidoong.attach(10);
  Yak2pusher.attach(11);
  Yak1gidoong.write(180);
  Yak1pusher.write(0);
  Yak2gidoong.write(180);
  Yak2pusher.write(0);
}

void loop() 
{
  if(Serial.available()){
    char c=(char)Serial.read();
    if(c=='1'){
      Serial.print("1");
      Abet();
      delay(5000);
    } 
    else if (c=='2'){
      Serial.print("2");     
      Bbet();
      delay(5000);
    }
    else if(c=='3'){
      Serial.print("3");
      Abet();
      Bbet();
      delay(5000);
    }
    else if(c=='0'){
      Serial.print("0");      
    }
    else{
      Serial.print("NaN");
    }
  }
}
