#include <HX711.h>
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define NOTE_C4 262


#define calibration_factor 450.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

HX711 scale (4,2);

Servo myservo1;
Servo myservo2;

int Buzz = 7;


void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
 


//lcd display
  Serial.begin(9600);
  lcd.begin(); // Turn on the blacklight
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart Pet");
  lcd.setCursor(0,1);
  lcd.print("Feeder");
  delay(3000);
  myservo1.attach(0);
  myservo2.attach(1);
  

}

void loop() {
  
  lcd.clear();
  lcd.print("Enter Weight");
  myservo1.write(10);
  myservo2.write(25);
  delay(5000);


          if (scale.get_units() < 5)
          {
            
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Opening");
          lcd.setCursor(0,1);
          lcd.print("the latch");
          delay(10000);
          tone(Buzz, NOTE_C4, 2000); // Play note C4, for 0.5 
          delay(1000); // Delay 1 second.  Delay is part of the 
          myservo1.write(105);
          delay(10000);
          myservo1.write(10);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("checking");
          lcd.setCursor(0,1);
          lcd.print("the hopper");
          delay(5000);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Dispensing food");
          delay(5000);
          Serial.print("Dispensed weight: ");
          Serial.print(scale.get_units());
          Serial.print("  grams ");
          Serial.println();
          myservo2.write(145);
          delay(7000);
          myservo2.write(25);
          delay(5000);

          }
          else if (scale.get_units() > 5) {
            
            lcd.clear();
            lcd.print("overweight");
            delay(2000);
            Serial.print("overweight");
            Serial.println();
            delay(2000);

          }

         
 
  

}