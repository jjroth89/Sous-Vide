# DIY Sous-Vide Temperature Control using Arduino
The DIY Sous-Vide Temperature Control program is an innovative solution to achieve precision temperature control in a homemade sous-vide setup. Using a Dallas DS18B20 waterproof temperature sensor, a 4x4 hex keypad, and two relay modules, this project allows you to easily control the temperature of your sous-vide bath.

This program utilizes the OneWire communication protocol, but instead of using the official OneWire library, it utilizes a modified version called OneWireNoResistor, created by bigjosh. This modification allows the code to work without the need for external pull-up resistors for the temperature sensors. Additionally, the program uses the DallasTemperature library to read the temperature, which is then triggered by a key press from the keypad.

The device will be loaded with preset options for different foods, as well as a feature to allow manual preset inputs, giving you ultimate control over your sous-vide cooking. With this project, you can achieve professional-grade results at a fraction of the cost of commercial sous-vide machines.

## Hardware Used
- Arduino UNO
- Dallas DS18B20 waterproof temperature sensor
- Generic 4x4 hex keypad
- Relay modules

## Libraries Used
- OneWireNoResistor library by bigjosh
- DallasTemperature library
- Keypad library
- LibPrintf library (for printf function)

## Arduino Connection Diagram
- Connect the temperature sensor data wire (yellow) to pin A1
- Connect the keypad rows to pins 9, 8, 7, 6
- Connect the keypad columns to pins 5, 4, 3, 2
- Connect the heat relay to pin A3
- Connect the pump relay to pin A4

## Setup
1. Download and install the OneWire, DallasTemperature, Keypad, and LibPrintf libraries from the Arduino Library Manager.
2. Connect the temperature sensor, keypad, and relay module to the Arduino as per the connection diagram.
3. Upload the code to the Arduino and open the serial monitor.
4. Press a key on the keypad to trigger a temperature reading. The reading will be displayed in the format:
```
Key pressed - DEV# - Temperature C
```

## Additional notes
- This code uses the OneWireNoResistor library created by bigjosh, instead of the official OneWire library. The reason for this is that this version eliminates the need for external pull-up resistors for the temperature sensors. It is important to note that the official version of the OneWire library will not work with this code.
- For more information on the OneWireNoResistor library by bigjosh, check out the documentation on his GitHub page: https://github.com/bigjosh/OneWireNoResistor
- For more information on the DallasTemperature library, check out the documentation on the official website: https://milesburton.com/Dallas_Temperature_Control_Library
- For more information on the Keypad library, check out the documentation on the official website: https://playground.arduino.cc/Code/Keypad/
- The LibPrintf library is used to enable the printf function for formatting the output in a more readable format.

## Features to be added
- Addition of temperature and time profiles for the relay module to control a heating source.
- Implementing a menu system for the keypad to make it more user-friendly.
- Adding the ability to set and display temperature thresholds for the sensor.
- Implementing a web-based interface for monitoring and controlling the temperature remotely.
- Implementing a data logging feature to record temperature readings over time and display them in a graph.
- Adding the ability to connect multiple temperature sensors to the system and display the readings from all of them.
- Implementing a password-protected system to restrict access to certain features, such as changing temperature thresholds or profiles.
- Adding the ability to send notifications or alerts when certain temperature thresholds are reached or exceeded.
- Integration with other smart home devices such as thermostats or home automation systems for seamless control and monitoring.
- Adding the ability to control the relay via voice commands through integration with virtual assistants such as Amazon Alexa or Google Assistant.
- Implementing a mobile app for remote monitoring and control of the temperature.

## Changelog
### v0.6
- Initial release of the program
- Includes temperature reading and display through keypad input and serial monitor output
- Optional relay module for controlling a heating source

### v0.7
- Included header comment
- Improved README.md
- Relocated the pins on the Arduino UNO board to get a more clean looking device
