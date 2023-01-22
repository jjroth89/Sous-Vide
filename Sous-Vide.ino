// This works to output key presses, device number and temperature.
// Next step is to add the switch control and create the profiles.

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
byte rowPins[ROWS] = {13, 12, 11, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

// Initialize keypad using defined layout and pin numbers
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Define pin number for OneWire bus and relay
#define ONE_WIRE_BUS 9
#define RELAY_PIN 7

// Initialize OneWire instance to communicate with devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass OneWire instance to Dallas Temperature library
DallasTemperature sensors(&oneWire);

void setup()
{
    // Configure the digital pins 8 and 10 as outputs to connect the DS18B20 sensor without a resistor
    pinMode(8, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);

    // Start the serial communication
    Serial.begin(9600);

    // Configure the relay pin as an output
    pinMode(RELAY_PIN, OUTPUT);

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
    }
}
