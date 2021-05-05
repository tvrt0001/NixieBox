// See SetupX_Template.h for all options available

// TFT_3.3V 1     ->    3V3   GREY
// TFT_GND  2     ->    GND   PURPLE
// TFT_CS   3     ->    15    BLUE
// TFT_RST  4     ->    4     GREEN 
// TFT_DC   5     ->    2     YELLOW
// TFT_MOSI 6     ->    23    ORANGE
// TFT_SCLK 7     ->    18    RED
// TFT_LED  8     ->    17    GREY2  (BACKLIGHT)
// TFT_MISO 9     ->    19    YELLOW2

#define ILI9341_DRIVER
#define TFT_CS    15    // Chip select control pin D15
#define TFT_RST   4     // Reset pin (could connect to NodeMCU RST, see next line)
#define TFT_DC    2     // Data Command control pin D02
#define TFT_MOSI  23    // Chip select control pin D23
#define TFT_SCLK  18    // Chip select control pin D18
#define TFT_BL    17    // BACKLIGHT (LED)
#define TFT_MISO  -1 //19    // Chip select control pin D19  
// #define TFT_RST  -1  // Set TFT_RST to -1 if the display RESET is connected to NodeMCU RST or 3.3V

// #define TFT_HEIGHT 240 // GC9A01 240 x 240
// #define TFT_WIDTH  320 // ST7789 240 x 240 and 240 x 320

#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//  #define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red

//#define TFT_INVERSION_ON
#define TFT_INVERSION_OFF

// #define TFT_BL   32            // LED back-light control pin
#define TFT_BACKLIGHT_ON HIGH  // Level to turn ON back-light (HIGH or LOW)

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT
#define SPI_FREQUENCY  27000000
//#define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  80000000
#define SPI_READ_FREQUENCY  20000000
//#define SPI_TOUCH_FREQUENCY  2500000
///#define SUPPORT_TRANSACTIONS
