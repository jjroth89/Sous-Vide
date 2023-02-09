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
 * @version 1.2.a
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

  // Start up the sensor's library
  sensors.begin();
  dbl("TEMPERATURE SENSORS INITIALIZED");


  // Configure the relay pins as outputs
  pinMode(HEAT_RELAY_PIN, OUTPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  dbl("RELAY PINS INITIALIZED");

  inputString.reserve(3); // maximum number of 3 digits for the input number
  dbl("BOOT COMPLETE");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    dbl(key);
    if (key == '*') {
      inputString = "";                 // clear input
      targetTemp = 0;
      cookingTime = 0;
      dbl("Initializing sous-vide setup.");
      dbl("Please type in the target temperature in Celsius and then press # to store it:");

    } else if (key >= '0' && key <= '9') {     // only act on numeric keys
        inputString += key;               // append new character to input string

    } else if (key == '#') {
        if (targetTemp == 0) {
          if (inputString.length() > 0) {
            inputInt = inputString.toInt();
            inputString = "";               // clear input
            targetTemp = inputInt;
            dbl("Target temperature set to " + String(targetTemp) + " degrees Celsius. Now please type in the cooking time in hours:");
          }

      } else if (cookingTime == 0) {
          if (inputString.length() > 0) {
            inputInt = inputString.toInt();
            inputString = "";               // clear input
            cookingTime = inputInt;
            dbl("Cooking time set to " + String(cookingTime) + " hours.");
            dbl("Please review the cooking settings:");
            dbl("Target temperature: " + String(targetTemp) + " degrees Celsius.");
            dbl("Cooking time: " + String(cookingTime) + " hours.");
            dbl("To confirm these settings and start the cooking cycle, press #. Otherwise press * to restart set up.");
          }

      } else if (cookingTime * targetTemp > 0 && key == '#') {
          if (digitalRead(PUMP_RELAY_PIN) == LOW) { 
            dbl("Starting the water pump.");
            digitalWrite(PUMP_RELAY_PIN, HIGH);

          while (true) {
            sensors.requestTemperatures();
            db("Current temperature: ");
            db(sensors.getTempCByIndex(0));
            db(" C - ");
            if (sensors.getTempCByIndex(0) < targetTemp) {
              dbl("Heating ON");
              digitalWrite(HEAT_RELAY_PIN, HIGH);
            } else {
              dbl("Heating OFF");
              digitalWrite(HEAT_RELAY_PIN, LOW);
            }
            dbl(key);
            delay(5000);  // delay 5 seconds between updates
          }
        }
      }
    }
  }
}