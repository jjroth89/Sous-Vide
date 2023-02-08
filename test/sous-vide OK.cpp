/**
 * DIY Sous-Vide Temperature Control using Arduino
 * 
 * Description:
 * This code uses a Keypad, a waterproof DS18B20 sensor, and relays
 * to control the temperature of a DIY Sous-Vide cooking setup.
 * 
 * Author: jjroth89
 * Date: January 2023
 * 
 * @author jjroth89
 * @version 1.1
 */

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Keypad.h>

// Define DEBUG mode to TRUE. If FALSE, all serial print commands will be removed when compiling
#define DEBUG 1

#if DEBUG == 1
#define db(x) Serial.print(x)
#define dbl(x) Serial.println(x)
#endif

// Define number of rows and columns for keypad
const byte ROWS = 4;
const byte COLS = 4;

// Define keypad button layout
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define row and column pin numbers for keypad
byte rowPins[ROWS] = {9, 8, 7, 6};      // Orange wires, ascending order
byte colPins[COLS] = {5, 4, 3, 2};      // White wires, ascending order

// Initialize keypad using defined layout and pin numbers
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Define OneWire bus, heat source and water pump pins
#define ONE_WIRE_BUS A0
#define HEAT_RELAY_PIN A1
#define PUMP_RELAY_PIN A2

// Declare target temperature and cooking duration variables
int targetTemp = 0;
int cookingTime = 0;

// Declare input operations variables
String inputString;
long inputInt;

// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our OneWire reference to the Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  delay(1500),
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  dbl("SERIAL PORT INITIALIZED");
  // Start up the library
  sensors.begin();
  dbl("TEMPERATURE SENSORS INITIALIZED");  
  inputString.reserve(3); // maximum number of 3 digits for the input number
  dbl("BOOT COMPLETE");  
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    dbl(key);
    if (key >= '0' && key <= '9') {     // only act on numeric keys
      inputString += key;               // append new character to input string
    } else if (key == '#') {
      if (inputString.length() > 0) {
        inputInt = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
        inputString = "";               // clear input
        dbl(inputInt);
        // Issue global temperature request to all devices on the bus
        sensors.requestTemperatures();
        db("Celsius temperature: ");
        dbl(sensors.getTempCByIndex(0));   // Index = 0 as there's only one temp sensor
      }
    } else if (key == '*') {
      inputString = "";                 // clear input
    }
  }
}
// THIS CODE IS WORKING:
// CHATGPT IS AWARE OF THIS CODE WORKING AND IS AWAITING FURTHER INSTRUCTIONS
// NEXT STEPS:
// Add a verification of the targetTemp and cookingTime variables in the beginning of the loop. If == 0, get input and store new value.