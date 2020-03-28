/* RTC + Servo
   Author @ Engr. Muhammad Taha
   0330-8530186
*/
#include <DS3231.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

DS3231  rtc(SDA, SCL); // Init the DS3231 using the hardware interface

const int rs = 12, en = 11, d4 = 5, d5 = 6, d6 = 7, d7 = 8;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Time  t;
int pos = 0;    // variable to store the servo position

void setup ()
{ rtc.begin();
  lcd.begin(16, 2);
  Serial.begin(115200);
  myservo.attach(9); // attaches the servo on pin 9 to the servo object


  // The following lines can be uncommented to set the date and time
  rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(10, 59, 30);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(3, 3, 2019);   // Set the date to January 1st, 2014
  delay(1000);
  myservo.write(pos);
}


void loop ()
{
  t = rtc.getTime();
  int H = t.hour;
  int M = t.min;
  int S = t.sec;

  if (H == 11 && M == 0 && S < 2 )
  {
    for (pos = 0; pos <= 50; pos += 1) // goes from 0 degrees to 50 degrees
    {
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(40);                       // waits 15ms for the servo to reach the position
    }
    Serial.print("Servo Angle 50 Degree ");
    Serial.println("");
  }

  Serial.print(rtc.getMonthStr());
  Serial.println("");
  Serial.print(rtc.getDateStr());
  Serial.println("");
  Serial.print(rtc.getTimeStr());
  Serial.println("-x-x-x--x-x--x-x--x-x");

  delay (1000);
}
