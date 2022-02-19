#include <Servo.h>
#define Yak1min 180
#define Yak1max 125
#define Yak2min 0
#define Yak2max 40
Servo Yak1;
Servo Yak2;
void setup()
{
  Yak1.attach(9);
  Yak2.attach(10);
  Yak2.write(5);
  for(;;)
  {
    Yak1.write(180);
    delay(100);
    Yak1.write(150);
    delay(100);
    Yak1.write(180);
    delay(100);
    Yak1.write(150);
    delay(100);
    Yak1.write(180);
    delay(100);
    Yak1.write(150);
    delay(100);
    Yak1.write(180);
    delay(100);
    Yak1.write(150);
    delay(100);
    Yak1.write(180);
    delay(100);
    Yak1.write(150);
    delay(100);
    Yak1.write(180);
    delay(300);
    for(int i=Yak1min;i>=Yak1max;i--)
    {
      Yak1.write(i);
      delay(30);
    }
    delay(100);
    for(int i=Yak2min;i<Yak2max;i++)
    {
      Yak2.write(i);
      delay(10);
    }
    for(int i=Yak2max;i>=Yak2min;i--)
    {
      Yak2.write(i);
      delay(10);
    }
    delay(1000);
  }
}
void loop(){}
