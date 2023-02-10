# DIY Sous-Vide Temperature Control using Arduino
The DIY Sous-Vide Temperature Control program is an innovative solution to achieve precision temperature control in a homemade sous-vide setup. Using a Dallas DS18B20 waterproof temperature sensor, a 4x4 hex keypad, and two relay modules, this project allows you to easily control the temperature of your sous-vide bath.

This program utilizes the OneWire communication protocol along the DallasTemperature library to read the temperature.

The device will be loaded with preset options for different foods, as well as a feature to allow manual preset inputs, giving you ultimate control over your sous-vide cooking. With this project, you can achieve professional-grade results at a fraction of the cost of commercial sous-vide machines.

## Hardware Used
- Arduino UNO
- Dallas DS18B20 waterproof temperature sensor
- Generic 4x4 hex keypad
- Relay modules

## Libraries Used
- OneWire
- DallasTemperature
- Keypad

## Arduino Connection Diagram
- Connect the temperature sensor data wire (yellow) to pin A1
- Connect the keypad rows to pins 9, 8, 7, 6
- Connect the keypad columns to pins 5, 4, 3, 2
- Connect the heat relay to pin A3
- Connect the pump relay to pin A4

## Setup
1. Download and install the OneWire, DallasTemperature and Keypad libraries.
2. Connect the temperature sensor, keypad, and relay module to the Arduino as per the connection diagram.
3. Upload the code to the Arduino and open the serial monitor.
4. Follow the serial output in order to setup the device and start using it.

## Features to be added
- Addition of temperature and time profiles.
- Implementing an OLED display to make it more user-friendly.
- Adding the ability to set and display temperature thresholds for the sensor.
- Implementing a data logging feature to record temperature readings over time and display them in a graph.
- Adding the ability to send notifications or alerts when certain temperature thresholds are reached or exceeded.
- Adding the ability to control the relay via voice commands through integration with virtual assistants such as Amazon Alexa or Google Assistant.
- Implementing a mobile app for remote monitoring and control of the temperature.

## Changelog
### v0.1.5 NoResistor
- Initial release of the program using the NoResistor version of OneWire library
- Includes temperature reading and display through keypad input and serial monitor output
- Optional relay module for controlling a heating source

### v0.1.6 NoResistor
- Included header comment
- Improved README
- Relocated the pins on the Arduino UNO board to get a more clean looking device

### v0.1.7 NoResistor
- Removed LibPrintf.h to reduce memory usage

### v0.2.0
- Restarted the project using official libraries and a 4.7k resistor to transition into the PlatformIO IDE which is more VSCode-friendly than the Arduino IDE previously used
- Implemented debug aliases to facilitate serial print removal upon deployment

### v0.2.1
- Implemented the ability to store numeric keypad inputs into integers

### v0.3.0
- Refactored versioning
- Completed cooking temperature and time setup
- Created a cycle loop that controls the temperature and duration
- Reduced the number of time-related operations

### Next release - v0.3.1
- TODO: Implement a check for '*' key press to reset the cycle
- TODO: Implement a progress bar in the output (on hold until OLED display arrives)