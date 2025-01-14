#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 
int pot_pin = A0;
int pot_value;
float Voltage;
float tempc;
float tempf;
int ledPin = 3;  // Pin for the red LED
int buzzerPin = 5; // Pin for the piezo buzzer
int tempPin = A0;
float highTemp = 75.0;
float lowTemp = 70.0;
float sensorValue;

void setup()
{
  lcd.init();
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(900);
}

void loop()
{
  pot_value = analogRead(pot_pin);
  Voltage = (pot_value/1023.0)*5;
  tempc = (Voltage-0.5)*100;
  tempf = (tempc*1.8)+32;
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temperature(F):");
  lcd.setCursor(0,1);
  lcd.print(tempf);
  lcd.setCursor(12,1);
  lcd.print("GOOD");
    if ((tempf > highTemp) || (tempf < lowTemp)) {
      while ((tempf > highTemp) || (tempf < lowTemp)) {
        digitalWrite(ledPin, HIGH);
        tone(buzzerPin, 1000);

        delay(350);

        digitalWrite(ledPin, LOW);
        noTone(buzzerPin);

        delay(350);
        pot_value = analogRead(pot_pin);
        Voltage = (pot_value/1023.0)*5;
        tempc = (Voltage-0.5)*100;
        tempf = (tempc*1.8)+32;
        lcd.backlight();
        lcd.setCursor(0,0);
        lcd.print("Temperature(F):");
        lcd.setCursor(0,1);
        lcd.print(tempf);
        lcd.setCursor(12,1);
        lcd.print(" BAD");
      }
  }
  delay(350);
}
