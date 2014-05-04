/*

Arduino Dev board

20 July 2013

Toby Robb

This is a test sketch for the Arduino Development board


NOTES:

LED / LCD  is the same pin, have only one or the other, is the LCD enable pin
RELAY is also the SCK pin *therefore may need to REMOVE relay jumper for programming
THERMISTOR / MOVEMENT SENSOR is the same pin, have only one or the other
LDR / SERVO  is the same pin, have only one or the other LOW turns on LCD

you must enable the internal pullups for the buttons by setting as inputs then writing HIGH
The leds if fitted also require the pullups to be enabled

*/

/*

TODO LIST

setup a spot to allow different features to be selected

#define USE_LCD
//#define USE_LED

#ifdef USE_LCD
  //define the setup for LCD here
  
else

//define the setup for LED's here

#endif


*/


// Includes

#include <Servo.h>   // Include the servo library
#include <Wire.h>
#include "RTClib.h"  //  For the clock
#include <LiquidCrystal.h>  //for the LCD

// Defines

#define ldrPin A3 // Light dependant resistor pin on board.
#define thermistorPin A2  //Temperature thermistor pin on board.
#define ledPin 4  // Led pin High for one colour Low for another
#define speakerPin A1  // The onboard speaker pin
#define relayPin 13 // Pin for the relay 

#define dataPin A4  // The I2C bus DATA pin  
#define clockPin A5  // The I2C CLOCK pin

#define potPin A0 // Potentiometer on the board.

#define button1Pin 12  // Button 1 pin
#define button2Pin 11 // Button 2 pin

#define gpio1Pin A2     // General Purpose Input/output 1 pin
#define gpio2Pin A3    // General Purpose Input/output 2 pin

#define mosfet1Pin  3  // Mosfet 1 drive pin
#define mosfet2Pin  9  // Mosfet 2 drive pin
#define mosfet3Pin  10  // Mosfet 3 drive pin

// declare some variables here if you like



Servo servo1;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int servoPos = 0;    // variable to store the servo position 

RTC_DS1307 RTC; // Date and time functions using a DS1307 RTC connected via I2C and Wire lib

/* initialize the lcd library with the numbers of the interface pins
* LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 4    //also the LED pin.. OFF to enable LCD
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 7
 * LCD D7 pin to digital pin 8
  */


LiquidCrystal lcd(2, 4, 5, 6, 7, 8);

               
void setup(){
  
// Setup the serial

  Serial.begin(9600);
  Serial.println("Beginning Setup");

// Set up the pins
 
  pinMode(ldrPin, INPUT);  // If the light sensor resistor is fitted
  pinMode(thermistorPin, INPUT);  // If the temperature sensor resistor is fitted
  pinMode(ledPin, OUTPUT);  // You MUST use this if the LED's are fitted.
  pinMode(relayPin, OUTPUT);  //  If the relay is fitted.
  pinMode(speakerPin, OUTPUT);  // If the speaker is fitted.
  pinMode(potPin, INPUT);  // If the potentiometer is fitted
  pinMode(button1Pin, INPUT);  // If the button is fitted (write HIGH to enable pullups)
  pinMode(button2Pin, INPUT);  // If the button is fitted (write HIGH to enable pullups)
  pinMode(mosfet1Pin, OUTPUT);  // Mosfet 1 output
  pinMode(mosfet2Pin, OUTPUT);  // Mosfet 2 output
  pinMode(mosfet3Pin, OUTPUT);  // Mosfet 3 output
  // default states   
  
servo1.attach(gpio2Pin);  // attaches the servo on pin gpio 2 to the servo object 

// default states   
//  digitalWrite(ledPin, LOW);  //ALSO turns on LCD enable
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, HIGH);
  digitalWrite(relayPin, LOW);
  digitalWrite(button1Pin, HIGH);  // enables pullups for buttons
  digitalWrite(button2Pin, HIGH);  // enables pullups for buttons
  
  servo1.write(0);
  
   
  Wire.begin();
   RTC.begin();
   if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // uncommenting the following line sets the RTC to the date & time this sketch was compiled
 //  RTC.adjust(DateTime(__DATE__, __TIME__));
  }

// set up the LCD's number of columns and rows: 
lcd.begin(16, 2);
lcd.clear();

}

void loop(){

lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print("www.tobyrobb.com");
delay(3000);

//beep the buzzer
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print(" Beeping buzzer ");

Serial.println("Beep");
tone(speakerPin, 500);          // begin tone at 1000 hertz
delay(150);                      // wait half a sec
noTone(speakerPin);              // end beep
delay(2000);

//Print the time and date to the serial port

DateTime now = RTC.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Time: ");
lcd.setCursor(6,0);
lcd.print(now.hour(), DEC);
lcd.setCursor(7,0);
lcd.print(":");
lcd.setCursor(10,0);
lcd.print(now.minute(), DEC);
lcd.setCursor(0,1);
lcd.print("Date: ");
lcd.setCursor(6,1);
lcd.print(now.day(), DEC);
lcd.setCursor(8,1);
lcd.print(":");
lcd.setCursor(9,1);
lcd.print(now.month(), DEC);
lcd.setCursor(11,1);
lcd.print(":");
lcd.setCursor(12,1);
lcd.print(now.year(), DEC);

delay(5000);

////flash the leds
//lcd.clear();
//lcd.setCursor(0,0);
//lcd.print("ArdDev Version 2");
//lcd.setCursor(0,1);
//lcd.print(" Flash the leds ");
//Serial.println("Flash the LED's");
//for(int i = 0; i<=8; i++){
//  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(100);               // wait for a second
//  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
//  delay(100);               // wait for a second
//}
//digitalWrite(ledPin, LOW);   // turn the LED off ALSO LCD enable
//
//delay(2000);

// Cycle the relay
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print("    Relay ON    ");
digitalWrite(relayPin, HIGH);
Serial.println("Relay ON");
delay(2000);
digitalWrite(relayPin, LOW);
Serial.println("Relay OFF");
lcd.setCursor(0,1);
lcd.print("   Relay OFF    ");
delay(2000);

// Test the mosfets
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print(" Mosfet 1 blink ");
Serial.println("Mosfet 1 blink");
digitalWrite(mosfet1Pin, HIGH);
delay(250);
digitalWrite(mosfet1Pin, LOW);
delay(2000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print(" Mosfet 2 blink ");
Serial.println("Mosfet 2 blink");
digitalWrite(mosfet2Pin, HIGH);
delay(250);
digitalWrite(mosfet2Pin, LOW);
delay(2000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print(" Mosfet 3 blink ");
Serial.println("Mosfet 3 blink");
digitalWrite(mosfet3Pin, HIGH);
delay(250);
digitalWrite(mosfet3Pin, LOW);
delay(2000);

// Sweep the servo on GPIO 2

//lcd.clear();
//lcd.setCursor(0,0);
//lcd.print("ArdDev Version 2");
//lcd.setCursor(0,1);
//lcd.print("Sweep the servo ");
//Serial.println("Sweep the servo");
//for(servoPos = 0; servoPos < 180; servoPos += 1)  // goes from 0 degrees to 180 degrees 
//  {                                  // in steps of 1 degree 
//    servo1.write(servoPos);              // tell servo to go to position in variable 'servoPos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//  for(servoPos = 180; servoPos>=1; servoPos-=1)     // goes from 180 degrees to 0 degrees 
//  {                                
//    servo1.write(servoPos);              // tell servo to go to position in variable 'servoPos' 
//    delay(15);                       // waits 15ms for the servo to reach the position 
//  } 
//delay(2000);
  
// Print the value of the button states
lcd.clear();
for(int i = 0; i <=500; i++){
lcd.setCursor(0,0);
lcd.print(" Button States  ");
lcd.setCursor(0,1);
lcd.print("B1 ");
lcd.setCursor(3,1);
lcd.print(digitalRead(button1Pin));
lcd.setCursor(5,1);
lcd.print("B2 ");
lcd.setCursor(8,1);
lcd.print(digitalRead(button2Pin));
}

Serial.print("Button one state : ");
Serial.println(digitalRead(button1Pin));
Serial.print("Button two state : ");
Serial.println(digitalRead(button2Pin));
delay(2000);

// Show the value of the LDR for a few seconds
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print("Brightness     ");
for(int i = 0; i <=500; i++){
  lcd.setCursor(15,1);
  lcd.print(analogRead(ldrPin));
Serial.print("The brightness : ");
Serial.println(analogRead(ldrPin));
}
delay(2000);


//show the value of the temperature thermistor for a few seconds
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print("Temp/movement ");
lcd.setCursor(0,1);
for(int i = 0; i <=500; i++){
  lcd.setCursor(14,1);
  lcd.print(analogRead(thermistorPin));
Serial.print("The Temperature : ");
Serial.println(analogRead(thermistorPin));
}
delay(2000);


// Print off the potentiometer value for a few seconds
lcd.clear();
lcd.setCursor(0,0);
lcd.print("ArdDev Version 2");
lcd.setCursor(0,1);
lcd.print("Potentiometer ");
lcd.setCursor(0,1);
for(int i = 0; i <=500; i++){
  lcd.setCursor(14,1);
  lcd.print(analogRead(potPin));
Serial.print("Potentiometer one : ");
Serial.println(analogRead(potPin));
}

delay(2000);

}
