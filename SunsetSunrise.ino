#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
 
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
const int buttonyellow1 =8; 
const int buttonyellow2 =12; 
const int buttonwhite1 = 10;  
const int buttonwhite2 = 11; 
int buttonStateyellow1 = 0;
int buttonStateyellow2 = 0;
int buttonStatewhite1 = 0;
int buttonStatewhite2 = 0;
int timehourrise = 0;
int timeminuterise = 00;
int timehourset = 0;
int timeminuteset = 00;
int blue = 5;     
int white = 3;   
int red = 4;    
int green = 2;      
 
 
RTC_DS3231 RTC;
LiquidCrystal_I2C lcd(0x27,16,2); 
 
void setup()
{
  lcd.begin();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Initialising...");
    lcd.createChar(2, clock);
  Wire.begin();
   RTC.begin();
   
}
 
void loop()
{
  lcd.clear();
   DateTime now = RTC.now();
   lcd.printByte(2);
   lcd.print(" ");
  lcd.print(now.hour(), DEC);
    lcd.print(':');
    lcd.print(now.minute(), DEC);
    lcd.print(':');
    lcd.print(now.second(), DEC);
   lcd.setCursor(0, 1);
   lcd.print(now.day(), DEC);
    lcd.print('/');
    lcd.print(now.month(), DEC);
    lcd.print('/');
    lcd.print(now.year(), DEC);
    lcd.print(' ');
  delay(1000);
  buttonStateyellow1 = digitalRead(buttonyellow1);  
  buttonStateyellow2 = digitalRead(buttonyellow2);  
  buttonStatewhite1 = digitalRead(buttonwhite1);
  buttonStatewhite2 = digitalRead(buttonwhite2);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonStateyellow1 == HIGH) {
   if (timehourrise == 24) {
      timehourrise = -1;
    }
    timehourrise = timehourrise + 1;
    lcd.clear();
    lcd.print("Wake up ");
    lcd.print(timehourrise);
    lcd.print(":");
    lcd.print(timeminuterise);
    delay(1000);
  }
  else if (buttonStateyellow2 == HIGH) {
    if (timeminuterise == 50) {
      timeminuterise = -10;
    }
    timeminuterise = timeminuterise + 10;
    lcd.clear();
    lcd.print("Wake up ");
    lcd.print(timehourrise);
    lcd.print(":");
    lcd.print(timeminuterise);
    delay(1000);
  }
  if (buttonStatewhite1 == HIGH) {
   if (timehourset == 24) {
      timehourset = -1;
    }
    timehourset = timehourset + 1;
    lcd.clear();
    lcd.print("To sleep ");
    lcd.print(timehourset);
    lcd.print(":");
    lcd.print(timeminuteset);
    delay(1000);
  }
  else if (buttonStatewhite2 == HIGH) {
    if (timeminuteset == 50) {
      timeminuteset = -10;
    }
    timeminuteset = timeminuteset + 10;
    lcd.clear();
    lcd.print("To sleep ");
    lcd.print(timehourset);
    lcd.print(":");
    lcd.print(timeminuteset);
    delay(1000);
  }

if (now.hour() == timehourrise && now.minute()==timeminuterise) {  
      // red fades in 
      for (float fadeValue = 0 ; fadeValue <= 225; fadeValue += 1) {
      // sets the value (range from 0 to 225):
      analogWrite(red, fadeValue);
      delay(75);
      }
       // green fades in
      for (float fadeValue = 0 ; fadeValue <= 75; fadeValue += 0.1875) {
      // sets the value (range from 0 to 125):
      analogWrite(green, fadeValue);
      delay(75);
      }                                                                                                                                                                                                                                                                      
      // white fades in
      for (float fadeValue = 0 ; fadeValue <= 225; fadeValue += 0.75) {
      // sets the value (range from 0 to 225):
      analogWrite(white, fadeValue);
      delay(75);
      }
     //red and green fade out
      for (float fadeValue = 225 ; fadeValue >= 0; fadeValue -= 3) {
      // sets the value (range from 0 to 1000):
      analogWrite(red, fadeValue);
      analogWrite(green, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(75);
      } 
      // blue fades in
      for (float fadeValue = 0 ; fadeValue <= 150; fadeValue += 0.375) {
      // sets the value (range from 0 to 225):
      analogWrite(blue, fadeValue);
      delay(75);
      }
      //blue and white fade out
      for (float fadeValue = 225 ; fadeValue >= 0; fadeValue -= 1) {
      // sets the value (range from 0 to 1000):
      analogWrite(blue, fadeValue);
      analogWrite(white, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(75);
      } 
  }
if (now.hour() == timehourset && now.minute()==timeminuteset) { 
       // red fades in 
      for (float fadeValue = 0 ; fadeValue <= 225; fadeValue += 0.25) {
      // sets the value (range from 0 to 225):
      analogWrite(red, fadeValue);
      delay(75);
      }
      // red fades out
      for (float fadeValue = 0 ; fadeValue <= 225; fadeValue -= 0.25) {
      // sets the value (range from 0 to 225):
      analogWrite(red, fadeValue);
      delay(75);
      }                                                                                                                                                                                                                                                                  
  }
  }
