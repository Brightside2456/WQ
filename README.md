# Water Quality Monitoring System

## Overview
This project implements a water quality monitoring system using an ESP32 microcontroller. It measures Total Dissolved Solids (TDS), pH, and temperature of water, providing real-time data for water quality analysis.

## Features
- Measures TDS (Total Dissolved Solids) in ppm
- Measures pH levels
- Measures water temperature in Celsius
- Serial output for easy monitoring
- Potential for IoT integration (commented out Blynk functionality)

## Hardware Requirements
- ESP32 Development Board
- TDS Sensor
- pH Sensor
- DS18B20 Temperature Sensor
- Jumper wires
- Power supply (USB or external)

## Pin Connections
- TDS Sensor: GPIO 2
- pH Sensor: GPIO 35
- DS18B20 Temperature Sensor: GPIO 4

## Libraries Required
- OneWire
- DallasTemperature

## Setup Instructions
1. Connect the sensors to the ESP32 as per the pin configuration.
2. Install the required libraries using the Arduino IDE Library Manager.
3. Upload the code to your ESP32 board.
4. Open the Serial Monitor to view the sensor readings.

## Usage
After uploading the code, the system will continuously read and display water quality parameters:
- TDS in ppm
- pH level
- Temperature in Celsius

The readings are displayed on the Serial Monitor at 115200 baud rate.

## Calibration
- The pH sensor may require calibration. Adjust the `calibration_value` in the code if needed.
- TDS readings might need calibration based on your specific sensor and water conditions.

## Troubleshooting
- Ensure all sensor connections are secure.
- Check if the serial output is showing reasonable values for each parameter.
- If a sensor is not working, try testing it individually with a basic example sketch.

## Future Enhancements
- Integration with Blynk for remote monitoring (code commented out in current version)
- Adding an OLED display for on-device reading display
- Implementing data logging functionality

## Contributing
Feel free to fork this project and submit pull requests for any enhancements or bug fixes.

## License
MIT License

## Contact
sefahb13@gmail.com