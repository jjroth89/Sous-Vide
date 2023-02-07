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
 * @version 1.0
 */

#include <OneWire.h>
#include <DallasTemperature.h>

// Define DEBUG mode to TRUE. If FALSE, all serial print commands will be removed when compiling
#define DEBUG 1

#if DEBUG == 1
#define db(x) Serial.print(x)
#define dbl(x) Serial.println(x)
#endif

// Define the OneWire bus pin
#define ONE_WIRE_BUS A0

// Setup a OneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our OneWire reference to the Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup()
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
}

void loop(){ 
  // Issue global temperature request to all devices on the bus
  sensors.requestTemperatures(); 
  
  db("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  db(sensors.getTempCByIndex(0)); 
  db(" - Fahrenheit temperature: ");
  dbl(sensors.getTempFByIndex(0));
  delay(1000);
}
