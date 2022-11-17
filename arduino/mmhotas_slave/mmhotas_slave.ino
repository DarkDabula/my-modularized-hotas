/**
 * Sketch for the slave board of the My Modularized HOTAS project
 * 
 * https://github.com/DarkDabula/my-modularized-hotas
 * 
 * Licensed with CC BY-NC 4.0
 * https://creativecommons.org/licenses/by-nc/4.0/
 */

#include "Wire.h"


/**
 * Here is general global stuff like definitions
 */

// Global debug flag, uncomment to enable serial port and outputs
//#define DEBUG 1

// Pins
#define pinSixButtons A0
#define pinHAT A1
#define pinTwoButtons A2
#define pinRocker A3

// Value tables to translate analog values into buttons
int valuesSixButtons[] = {75, 120, 160, 215, 300, 465};
int valuesHAT[] = {110, 145, 185, 255, 280, 435, 455, 340}; // N, NW, W, SW, S, SE, E, NE
int valuesTwoButtons[] = {200, 405, 335}; // 1, 2, 1+2
int valuesRocker[] = {405, 195}; // right, left

// Defines a range around the input value for comparison with the value tables
#define valueValidDelta 9

volatile int buttonStates = 0;

/**
 * Helper functions
 */

// Function to translate analogue values into button states
int evaluateInput(short pinInput, int valuesArray[], size_t arraySize, const char* title)
{
  int valueIO = analogRead(pinInput); 
  int outputValue = 0;
  #ifdef DEBUG
    Serial.print(title);
    Serial.print(": ");
    Serial.println(valueIO);
  #endif
  if(valueIO) 
  { 
    for(size_t i = 0; i < arraySize; i++)
    {
      if(abs(valueIO - valuesArray[i]) <= valueValidDelta)
      {
        outputValue = i+1;
        break;
      }
    }
  }
  #ifdef DEBUG
    Serial.print(" -> Translated: ");
    Serial.println(outputValue);
  #endif
  return outputValue; 
}

// Translates the different button values into one fot I2C transmission
// Each button group will be coded into 4 bits even it would need fewer bits
// Scheme will be:
// Bits 0 to 3: SixButtons group
// Bits 4 to 7: HAT
// Bits 8 to 11: TwoButtons group
// Bits 12 to 15: Rocker
int translateButtonValues(int valSixButtons, int valHAT, int valTwoButtons, int valRocker)
{
  int result = 0;

  result |= (valSixButtons & 0xF);
  result |= (valHAT & 0xF) << 4;
  result |= (valTwoButtons & 0xF) << 8;
  result |= (valRocker & 0xF) << 12;
  
  return result;
}

// EVent handler when the master requests the actual button states
void sendButtonStates()
{
  #ifdef DEBUG
    Serial.print("Sending button states to master: ");
    Serial.println(buttonStates);
  #endif  

  // LED on
  TXLED1;
  
  // Maybe dirty but we handle the int as an array of bytes
  Wire.write((const byte*)&buttonStates, sizeof(int));

  // LED off
  TXLED0;
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

  // Set up the input pins
  /*pinMode(pinSixButtons, INPUT);
  pinMode(pinHAT, INPUT);
  pinMode(pinTwoButtons, INPUT);
  pinMode(pinRocker, INPUT);*/

  // Set up I2C bus
  Wire.begin(0x11); // We are the slave
  Wire.onRequest(sendButtonStates);

}

/**
 * Main loop
 */
void loop() 
{
  int valueSixButtons = 0;
  int valueHAT = 0;
  int valueTwoButtons = 0;
  int valueRocker = 0;

  // LED on
  RXLED1;
  
  // Read SixButtons
  valueSixButtons = evaluateInput(pinSixButtons, valuesSixButtons, sizeof(valuesSixButtons) / sizeof(int), "SixButtons");

  // Read HAT
  valueHAT = evaluateInput(pinHAT, valuesHAT, sizeof(valuesHAT) / sizeof(int), "HAT");

  // Read TwoButtons
  valueTwoButtons = evaluateInput(pinTwoButtons, valuesTwoButtons, sizeof(valuesTwoButtons) / sizeof(int), "TwoButtons");

  // Read rocker
  valueRocker = evaluateInput(pinRocker, valuesRocker, sizeof(valuesRocker) / sizeof(int), "Rocker");

  // Translate states
  buttonStates = translateButtonValues(valueSixButtons, valueHAT, valueTwoButtons, valueRocker);

  // LED off
  RXLED0;

  // Sleep for a while
  #ifdef DEBUG
    delay(500);
  #else
    delay(50);
  #endif
}
