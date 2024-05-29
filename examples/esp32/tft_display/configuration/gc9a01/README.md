## Installation of GC9A01 display for ESP32

Tools -> Manage Libraries, then search for "TFT_eSPI" and install it.

Edit the library configuration by opening the User_Setup.h file in the libraries folder (within your Arduino/libraries folder).

Uncomment the line `#define #define GC9A01_DRIVER` and comment out the other `#define` lines for other displays.

Uncomment the following lines:
`#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red`
`#define TFT_WIDTH  240`
`#define TFT_HEIGHT 240`

Scroll to the section for the ESP-32 (the line that reads `// ###### EDIT THE PIN NUMBERS IN THE LINES FOLLOWING TO SUIT YOUR ESP32 SETUP   ######`) and edit the following lines to match your wiring:

```
// #define TFT_MISO 34 // I didn't need this
#define TFT_MOSI 17
#define TFT_SCLK 18
 #define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)
```

Then you can use the examples in this folder, or sketches from Examples -> TFT_eSPI to test the display.

Video for reference: https://www.youtube.com/watch?v=HoZhgNcJjNA

## Audio Conflicts

The speaker crackles when refreshing the screen, I assume this is due to a pin conflict or power issue. I will investigate.