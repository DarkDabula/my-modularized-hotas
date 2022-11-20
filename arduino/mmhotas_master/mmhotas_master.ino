 /**
 * Sketch for the master board of the My Modularized HOTAS project
 * 
 * https://github.com/DarkDabula/my-modularized-hotas
 * 
 * Licensed with CC BY-NC 4.0
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

/**
 * Includes
 */

// Needed for I2C
#include "Wire.h"

// Joystick HID - Source: https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0
#include <Joystick.h>

// TOF Sensor
// Library from Pololu - Source https://github.com/pololu/vl53l0x-arduino
#include "VL53L0X.h"

/**
 * Here is general global stuff like definitions
 */

// Global debug flag, uncomment to enable serial port and outputs
//#define DEBUG 1

// Joystick object - 8 Buttons, one HAT, rudder and throttle
Joystick_ Joystick = Joystick_(0x04, JOYSTICK_TYPE_JOYSTICK, 8, 1, false, false, false, false, false, false, true, true, false, false, false);

// TOF Sensor for throttle
VL53L0X lox = VL53L0X();

// Main throttle table to translate distance values into throttle values
// Format is minDist, throttleVal
// throttleVal is defined as
//    -100, 100 - min/max
//    -1, 1     - linear range
//    0         - center 
//
int throttleTable[6][2] = 
{
  {-999, 100},  // 100%
  {5, 1},       // linear +
  {105, 0},     // 0%
  {115, -1},    // linear -
  {190, -100}   // -100%
};

// Zone around the center position considered as center in millimeters
int throttleCenterZone = 7;

/**
 * Helper functions
 */
 void initJoystick()
 {
   // Setup joystick
   Joystick.setThrottleRange(-100, 100);
   Joystick.setRudderRange(-100, 100);
   
   Joystick.begin(false);
   Joystick.setThrottle(0);
   Joystick.setRudder(0);
 }

 void initLOX()
 {
    // Measuring timeout is 100ms
    while(!lox.init()) delay(10);
    lox.setMeasurementTimingBudget(50000);
    delay(2000);

    // Take some measurements to retrive actual center value
    int throttleCenter = lox.readRangeSingleMillimeters();
    for(int i = 0; i < 10; i++)
    {
      throttleCenter += lox.readRangeSingleMillimeters();
      throttleCenter /= 2;
    }

    // With the actual center value we change the center range in the throttle table
    throttleTable[2][0] = throttleCenter - throttleCenterZone;
    throttleTable[3][0] = throttleCenter + throttleCenterZone;
 }

 // Translate external states into Joystick state
 //
 // @param tofPos Positions on TOF sensor in millimeters
 // @param buttonStates Button states reported by the slave adruino. The value have the following format
 //         Bits 0 to 3: SixButtons group (value 0 to 6)
 //         Bits 4 to 7: HAT (value 0 to 8)
 //         Bits 8 to 11: TwoButtons group (value 0 to 2)
 //         Bits 12 to 15: Rocker (value 0 to 2)
 //
 void sendJoystickState(int tofPos, int buttonStates)
 {
    signed short val = 0;
  
    // Translate throttle
    //
    signed short throttleValue = 0;
    unsigned short throttleEntry = 0; 
   
    #ifdef DEBUG
      Serial.println("Calculating throttle:");
    #endif
  
    for(short i = 0; i < 5; i++)
    {
      // Find the last matching entry
      if(tofPos >= throttleTable[i][0])
      {
        throttleValue = throttleTable[i][1];
        throttleEntry = i; 
      }
      else break;
    }

    #ifdef DEBUG
      Serial.print("- Found throttle table entry ");
      Serial.print(throttleEntry);
      Serial.print(" with value ");
      Serial.println(throttleValue);        
    #endif
 
    // When within a linear interval, do some calculations
    if(abs(throttleValue) == 1)
    {
      // This part is a bit tricky because we have to use the next table entry to calculate the linear value wthin the range
      int intervalRange = abs(throttleTable[throttleEntry][0] - throttleTable[throttleEntry + 1][0]);  
      #ifdef DEBUG
        Serial.print("- Linear range is: ");
        Serial.println(intervalRange);
      #endif

      // Here we calculate the distance from reference point debending on the direction
      int distanceToReference = (throttleValue > 0) ? (throttleTable[throttleEntry + 1][0] - tofPos) : (tofPos - throttleTable[throttleEntry][0]);
      #ifdef DEBUG
        Serial.print("- Distance to reference is: ");
        Serial.println(distanceToReference);
      #endif

      // With the range and distance we can do simple calculation of percent but we have to regard the sign
      throttleValue = throttleValue * 100.0 * (distanceToReference) / intervalRange;
    }

    #ifdef DEBUG
      Serial.print("Throttle: ");
      Serial.println(throttleValue);
    #endif
    Joystick.setThrottle(throttleValue);

    // Translate buttons
    //
    #ifdef DEBUG
      Serial.print("Buttons: ");
    #endif

    // Buttons 0 and 1
    val = (buttonStates >> 8) & 0xF;
    switch(val)
    {
      case 1:
        Joystick.pressButton(0);
        Serial.print("1 ");
        break;
        
      case 2:
        Joystick.pressButton(1);
        Serial.print("2 ");
        break;
        
      case 3: 
        Joystick.pressButton(0);
        Joystick.pressButton(1);
        Serial.print("1+2 ");
        break;
        
      default:
        Joystick.releaseButton(0);
        Joystick.releaseButton(1);
        break;  
      
    }
    
    // Buttons 2 to 8
    val = buttonStates & 0xF;
    for(int i = 1; i <= 6; i++)
    {
      if(val == i)
      {
        Joystick.pressButton(i+1);
        #ifdef DEBUG
          Serial.print(i+2);
          Serial.print(" ");
        #endif
      }
      else Joystick.releaseButton(i+1);
    }
    #ifdef DEBUG
      Serial.println("");
    #endif

    // Translate HAT
    //
    signed short angleHAT = JOYSTICK_HATSWITCH_RELEASE; // Released at begin
    val = (buttonStates >> 4) & 0xF;
    if(val > 0) angleHAT = (val - 1) * 45;
    #ifdef DEBUG
      Serial.print("HAT: ");
      Serial.println(angleHAT);
    #endif
    Joystick.setHatSwitch(0, angleHAT);

    // Translate rudder
    //
    signed rudderValue = 0;
    val = (buttonStates >> 12) & 0xF;
    // 2 is left -> -100, 1 is right -> 100
    //if(val > 0) rudderValue = val * -100 / val; 
    switch(val)
    {
      case 1:
        rudderValue = 100;
        break;

      case 2:
        rudderValue = -100;
        break;
    }
    #ifdef DEBUG
      Serial.print("Rudder: ");
      Serial.println(rudderValue);
    #endif
    Joystick.setRudder(rudderValue);
    
    // Send state to computer
    //
    Joystick.sendState();
 }


/**
 * Setup routine
 */
void setup() 
{
  // Setup serial port for debugging
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  
  // Set up I2C bus, needed for slave Arduino and TOF Sensor
  Wire.begin(); // We are the master

  // Setup joystick device
  initJoystick();

  // Setup TOF sensor
  initLOX();
}

/**
 * Main loop
 */
void loop() 
{
  // LED ON
  RXLED1;
  
  // Read and handle TOF
  static int tofLastPos = 0;
  int tofPos = lox.readRangeSingleMillimeters();
  #ifdef DEBUG
    Serial.print("TOF reports: ");
    Serial.println(tofPos);
  #endif

  // Smothing the value a little bit
  tofPos = (tofPos + tofLastPos) / 2;
  tofLastPos = tofPos;

  // LED off
  RXLED0;
  TXLED1;

  // Read slave arduino, its pervert because I2C only reads bytewise
  byte bytesBuffer[sizeof(int)];
  Wire.requestFrom(0x11, sizeof(int));
  while(Wire.available() != sizeof(int)) 
  {
  #ifdef DEBUG
    Serial.println("Waiting for slave ...");
  #endif
    delay(10);
  }  
  for(int i = 0; i < sizeof(int); i++)
  {
    bytesBuffer[i] = Wire.read();
    #ifdef DEBUG
      Serial.print("Receiving byte: ");
      Serial.println(bytesBuffer[i]);
    #endif
  }
  int buttonStates = *((int*)bytesBuffer);
  if(true) // Not needed anymore
  //if(buttonStates >= 0 && buttonStates < 10000) // Sometimes there are invalid values for what reason
  {
    #ifdef DEBUG
      Serial.print("Slave reports: ");
      Serial.println(buttonStates);
    #endif
  }
  else
  {
    #ifdef DEBUG
      Serial.print("Ignoring slave: ");
      Serial.println(buttonStates);
    #endif  
    buttonStates = 0;
  }

  // Translate and send joystick state
  sendJoystickState(tofPos, buttonStates);

  // LED off
  TXLED0;

  // Sleep for a while, only in debug because TOF sensor limits the cycle
  #ifdef DEBUG
    delay(500);
  //#else
  //  delay(50);
  #endif
}
