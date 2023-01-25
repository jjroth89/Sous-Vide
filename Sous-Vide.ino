/**
 * DIY Sous-Vide Temperature Control using Arduino
 * 
 * Description:
 * This code uses a Keypad, a waterproof DS18B20 sensor, and relays
 * to control the temperature of a DIY Sous-Vide cooking setup.
 * Instead of using the official OneWire library, this code uses a
 * modified version called OneWireNoResistor, created by bigjosh.
 * This modification allows the code to work without the need for
 * external pull-up resistors for the temperature sensors.
 * 
 * Author: jjroth89
 * Date: January 2023
 * 
 * Resources:
 * - OneWire library modified by bigjosh:
 * https://github.com/bigjosh/OneWireNoResistor
 * - Article explaining the modification:
 * https://wp.josh.com/2014/06/23/no-external-pull-up-needed-for-ds18b20-temp-sensor/
 * 
 * @author jjroth89
 * @version 0.7.1
 */


#include <OneWire.h>
#include <DallasTemperature.h>
#include <Keypad.h>
#include <LibPrintf.h>

// Define number of rows and columns for keypad
const byte ROWS = 4; 
const byte COLS = 4; 

// Declare variable to store number of devices
int numberOfDevices;

// Define keypad button layout
char hexaKeys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define row and column pin numbers for keypad
byte rowPins[ROWS] = {9, 8, 7, 6};   // Orange wires, ascending order
byte colPins[COLS] = {5, 4, 3, 2};      // White wires, ascending order

// Initialize keypad using defined layout and pin numbers
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Define pin number for OneWire bus and relays
#define ONE_WIRE_BUS A1
#define HEAT_RELAY_PIN A3
#define PUMP_RELAY_PIN A4

// Initialize OneWire instance to communicate with devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass OneWire instance to Dallas Temperature library
DallasTemperature sensors(&oneWire);

void setup()
{
    // Configure the digital pins A0 and A2 as outputs to connect the DS18B20 sensor without a resistor
    pinMode(A0, OUTPUT);
    pinMode(A2, OUTPUT);
    digitalWrite(A0, LOW);
    digitalWrite(A2, LOW);

    // Start the serial communication
    Serial.begin(9600);

    // Configure the relay pins as outputs
    pinMode(HEAT_RELAY_PIN, OUTPUT);
    pinMode(PUMP_RELAY_PIN, OUTPUT);

    // Wait for 1500ms before displaying the message
    delay(1500);
    printf("SETUP OK.\nPress a key from the keypad to get the temperature reading:\n");
}


void loop()
{
    // Begin communication with Dallas Temperature sensors
    sensors.begin();
    // Get the number of devices connected
    numberOfDevices = sensors.getDeviceCount();
    // Check if a key press is detected
    char customKey = customKeypad.getKey();
    if (customKey)
    {
        DeviceAddress tempDeviceAddress;
        // Loop through all connected devices
        for (int i = 0; i < numberOfDevices; i++)
        {
            // Get the device address
            if (sensors.getAddress(tempDeviceAddress, i))
            {
                // Request temperature from device
                sensors.requestTemperatures();
                // Get the temperature in Celsius
                float tempC = sensors.getTempC(tempDeviceAddress);
                // Print the key press, device number, and temperature to the serial monitor
                printf("%c - DEV%i - %.2fC\n", customKey, i, tempC);
            }
        }

        // Toggles heat relay ON/OFF on "*" key press
        if (customKey == '*')
        {
            if(digitalRead(HEAT_RELAY_PIN) == LOW)
            {
                digitalWrite(HEAT_RELAY_PIN, HIGH);
                printf("Heat relay ON\n");
            }
            else
            {
                digitalWrite(HEAT_RELAY_PIN, LOW);
                printf("Heat relay OFF\n");
            }
        }
    }
}
