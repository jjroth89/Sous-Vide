# DIY Sous-Vide Temperature Control using Arduino
This program is designed to control the temperature of a DIY sous-vide setup using a Dallas DS18x20 temperature sensor, a 4x4 hex keypad, and an optional relay module. The temperature sensor uses the OneWire communication protocol and the DallasTemperature library to read the temperature, which is then triggered by a key press from the keypad. The temperature readings are displayed in the serial monitor, allowing for easy monitoring and control of the sous-vide cooking process.

## Hardware Used
- Arduino board (compatible with the DallasTemperature library)
- Dallas DS18x20 temperature sensor
- 4x4 hex keypad
- Relay module (optional)

## Libraries Used
- OneWire library
- DallasTemperature library
- Keypad library
- LibPrintf library (for printf function)

## Connection Diagram
- Connect the temperature sensor data wire to pin 9 on the Arduino
- Connect the keypad rows to pins 13, 12, 11, and 6 on the Arduino
- Connect the keypad columns to pins 5, 4, 3, and 2 on the Arduino
- Connect the relay module to pin 7 on the Arduino (optional)

## Setup
1. Download and install the OneWire, DallasTemperature, Keypad, and LibPrintf libraries from the Arduino Library Manager.
2. Connect the temperature sensor, keypad, and relay module to the Arduino as per the connection diagram.
3. Upload the code to the Arduino and open the serial monitor.
4. Press a key on the keypad to trigger a temperature reading. The reading will be displayed in the format:
```
Key pressed - DEV# - Temperature C
```

## Additional notes
- Make sure to have the flat side of the temperature sensor facing the center of the board to ensure proper connection.
- The LibPrintf library is used to enable the printf function for formatting the output in a more readable format.
- For more information on the DallasTemperature library, check out the documentation on the official website: https://milesburton.com/Dallas_Temperature_Control_Library
- For more information on the Keypad library, check out the documentation on the official website: https://playground.arduino.cc/Code/Keypad/

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
- Optional relay module for controlling a heating source in a DIY sous-vide setup
