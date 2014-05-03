/*

Arduino Dev board

24 December 2013

Toby Robb

This is a test sketch for the Arduino Development board 2


NOTES:

You must enable the internal pullups for the buttons by setting as inputs then writing HIGH
The leds if fitted also require the pullups to be enabled

*/

// Includes


// Defines

#define ldrPin A3 // Light dependant resistor pin on board.
#define thermistorPin A2  //Temperature thermistor pin on board.
#define ledPin 4  // Led pin High for one colour Low for another
#define speakerPin A1  // The onboard speaker pin
#define relayPin 13 // Pin for the relay 

#define dataPin A4  // The I2C bus DATA pin  
#define clockPin A5  // The I2C CLOCK pin

#define potPin A0 // Potentiometer on the board.

#define button1Pin 11  // Button 1 pin
#define button2Pin 12 // Button 2 pin

#define gpio1Pin 5     // General Purpose Input/output 1 pin
#define gpio2Pin 6    // General Purpose Input/output 2 pin
#define gpio3Pin 11    // General Purpose Input/output 3 pin

#define mosfet1Pin  3  // Mosfet 1 drive pin
#define mosfet2Pin  9  // Mosfet 2 drive pin
#define mosfet3Pin  10  // Mosfet 3 drive pin

// declare some variables here if you like


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
  
  digitalWrite(button1Pin, HIGH);  // enables pullups for buttons
  digitalWrite(button2Pin, HIGH);  // enables pullups for buttons
  
  digitalWrite(mosfet1Pin, LOW);  // MOSFET's OFF
  digitalWrite(mosfet2Pin, LOW);
  digitalWrite(mosfet3Pin, LOW);
  digitalWrite(ledPin, HIGH);    // One LED on    
  digitalWrite(dataPin, HIGH);  
  digitalWrite(clockPin, HIGH);
  digitalWrite(relayPin, LOW);  // Relay off
   
}

void loop(){

 
}

  
