#include <LCD_I2C.h>
LCD_I2C lcd(0x27); // Default address of most PCF8574 modules, change according
#include <VarSpeedServo.h> 
VarSpeedServo servo1, servo2;
int pot = A3;
int button1 = 7;
int button2 = 6;
int Speed = 0;
int Angle = 75;
int AnglePos = 0;
int pos = 0; 
bool stp = true;
const byte interruptPin = 2;

void setup(){
    Serial.begin(9600);
    lcd.begin(); 
    lcd.backlight();
    pinMode(pot, INPUT);
    pinMode (button1, INPUT_PULLUP);
    pinMode (button2, INPUT_PULLUP);
    servo1.attach(9);
    servo1.write(0);
    servo2.attach(10);
    servo2.write(0);
    pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin),StpStrt, FALLING);
}


void loop(){
    
    int potVal = analogRead(pot);
    //Serial.println(potVal);
    lcd.setCursor (0,0);
    lcd.print("Pot: "); 
    lcd.setCursor(5, 0); 
    lcd.print(potVal);
      if (potVal < 1000){ lcd.setCursor(8,0); lcd.print(" ");}
      if (potVal < 100){ lcd.setCursor(7,0); lcd.print("  ");}
      if (potVal < 10){ lcd.setCursor(6,0); lcd.print("   ");}
   
   Speed = map(potVal, 0, 1023, 10, 255);
      lcd.setCursor (10,0); lcd.print("Sp:");
      lcd.setCursor (13,0); lcd.print(Speed);
        if (Speed < 100){ lcd.setCursor (15,0); lcd.print(" ");}
        if (Speed < 10){ lcd.setCursor (14,0); lcd.print("  ");}
        
    
    if (digitalRead(button1) == LOW){ if (Angle != 150) {Angle++; delay(150);}}
    if (digitalRead(button2) == LOW) {if (Angle != 0)   {Angle--; delay(150);}}
    lcd.setCursor (0,1); lcd.print ("Angle: ");
    lcd.setCursor (7,1); lcd.print (Angle);
      if (Angle < 100){ lcd.setCursor (9,1); lcd.print(" ");}
      if (Angle < 10){ lcd.setCursor (8,1); lcd.print("  ");}
 
    Serial.println (Speed);
 if (stp == false){ 
  servo1.stop();
 }
 if (stp == true){
 servo1.write(Angle,Speed,true);
 servo1.write(0,Speed,true);}
 
}

void StpStrt(){
  stp = !stp;
  delay (1000);
}
    

    
