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
#define dbp(x, precision) Serial.print(x, precision)
#define dblp(x, precision) Serial.println(x, precision)
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
int targetTemp = 0;             // HOURS
unsigned long cookingTime = 0;  // CELSIUS

// Declare input operations variables
String inputString;
int inputInt;

// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our OneWire reference to the Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup() {
  delay(1500),
  // Start serial communication for debugging purposes
  Serial.begin(9600);

  //! These lines are for better viewing the serial monitor.
  //! Looks like shit but works... Will be dropped soon.
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  dbl();
  
  dbl("SERIAL PORT INITIALIZED");

  // Start up the sensor's library
  sensors.begin();
  dbl("TEMPERATURE SENSORS INITIALIZED");


  // Configure the relay pins as outputs
  pinMode(HEAT_RELAY_PIN, OUTPUT);
  pinMode(PUMP_RELAY_PIN, OUTPUT);
  dbl("RELAY PINS INITIALIZED");

  inputString.reserve(3); // Reserve 3 digits for the input number
  dbl("BOOT COMPLETE");
  dbl();
  dbl("Press '*' to start the sous-vide setup...");
  dbl();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    db(key);
    if (key == '*') {
      inputString = "";                 // clear input
      targetTemp = 0;
      cookingTime = 0;
      dbl("Initializing sous-vide setup...");
      dbl();
      dbl("Please type in the target temperature in Celsius and then press '#' to store it:");

    } else if (key >= '0' && key <= '9') {     // only act on numeric keys
        inputString += key;               // append new character to input string

    } else if (key == '#') {
        if (targetTemp == 0) {
          if (inputString.length() > 0) {
            inputInt = inputString.toInt();
            inputString = "";               // clear input
            targetTemp = inputInt;
            dbl();
            dbl("Target temperature set to " + String(targetTemp) + "º Celsius.");
            dbl();
            dbl("Now please type in the cooking time in hours:");
          }

      } else if (cookingTime == 0) {
          if (inputString.length() > 0) {
            inputInt = inputString.toInt();
            inputString = "";                   // Clear input
            cookingTime = inputInt;
            dbl();
            dbl("Cooking time set to " + String(cookingTime) + " hours.");
            dbl();
            dbl("Please review the cooking settings:");
            dbl();
            dbl("Target temperature .... " + String(targetTemp) + " º Celsius.");
            dbl("Cooking time .......... " + String(cookingTime) + " hours.");
            dbl();
            dbl("Press '#' to confirm and start cooking.");
            dbl("Otherwise press * to restart set up.");
          }

      } else if (cookingTime * targetTemp > 0 && key == '#') {
          // Cycle starts here
          cookingTime = inputInt * 3.6e6;       // Transform hours to milliseconds
          const unsigned long cycleStartTime = millis();
          if (digitalRead(PUMP_RELAY_PIN) == LOW) {
            dbl();
            dbl("Starting the water pump.");
            digitalWrite(PUMP_RELAY_PIN, HIGH);
            unsigned long cycleRunningTime = millis() - cycleStartTime;
            unsigned long cycleRemainingTime = 1;

          while (cycleRemainingTime > 0 && key != '*') {
            cycleRunningTime = millis() - cycleStartTime;
            // Check whether the remaining time is greater than or equal to 0.
            // If TRUE, assign it to the variable. If FALSE, assign 0.
            // This prevents cycleRunningTime to overflow
            cycleRemainingTime = (cookingTime + cycleStartTime - millis() >= 0) ?
            (cookingTime + cycleStartTime - millis()) : 0;
            sensors.requestTemperatures();
            db("Current temperature: ");
            db(sensors.getTempCByIndex(0));
            dbl("ºC");
            db("Target temperature: ");
            db(targetTemp);
            db("ºC - ");
            if (sensors.getTempCByIndex(0) < targetTemp) {
              dbl("Heating ON");
              digitalWrite(HEAT_RELAY_PIN, HIGH);
            } else {
              dbl("Heating OFF");
              digitalWrite(HEAT_RELAY_PIN, LOW);
            }
            db("Cycle running time: ");
            dblp(cycleRunningTime / 3.6e6, 5);  //reverting back to seconds for debugging purposes
            db("Remaining time: ");
            dblp(cycleRemainingTime / 3.6e6, 5);
            dbl();
            delay(5000);
          }
        }
      }
    }
  }
}