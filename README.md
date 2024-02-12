# Mini Companion Robot 
Mini companion robot using ESP-32. There is also a legacy Arduino version available in the examples folder. 

## Note
This project is still in development. The hardware and software are subject to change.

## Future Plans

This project utilises the ESP-32 to create a pocket-sized companion robot.

The robot has (or will have) the following components that can be programmed with various example sketches (see the `examples` folder):

- ESP-32 microcontroller
- OLED display (see the `examples/esp32/st7789/README.md` for installation instructions)
- Speaker
- Microphone
- RGB Neopixel LED
- Gesture Sensor
- Motion Sensor
- Accelerometer
- Gyroscope
- Magnetometer
- Capacitive Touch Sensors
- Manual Power Switch
- Volume Control Knob
- Micro SD Card Slot
- 3.6V LiPo Battery
- USB-C Charging Port

Components all support 3.3V to minimise power consumption and to simplify the design. The battery is charged via USB-C and the robot can be programmed via USB-C. The robot can be programmed using the Arduino IDE. Over the air (OTA) updates are also supported.

The robot can be (or will be) programmed to demonstrate features such as:

- Internet radio player
- MP3 player (from Micro SD card)
- Voice recognition
- Voice synthesis
- Translator
- Gesture control
- Tilt control
- Capacitive touch control
- Play games
- Display animations (moving eye etc.)
- Night light
- Security alarm
- Weather station
- Clock
- Timer
- Stopwatch
- Compass (?)
- Pedometer
- Chatbot
- Bluetooth connectivity
- WiFi connectivity

The functionality is designed to be modular, so the robot can be configured to have the desired features. Simply select the modules you would like to install and upload the sketch to the robot. (Not yet implemented)