/*
   Arduino LCD I2C Tutorial by 'Tronics Lk"
   Please visit my YouTube channel from this link for more Tutorials
   https://www.youtube.com/channel/UCYJa3gs8q49-N3TLm-7ygUw?sub_confirmation=1
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
 
void setup()
{
  Wire.begin(D3, D4);  //SDA D3 --- SCL D4
  lcd.init();         // initialize the lcd
  lcd.backlight();  
  lcd.setCursor(1, 0);
  lcd.print("Mingalr!");  // Turn on the LCD screen backlight
}

void loop()
{
  
  
  
}
