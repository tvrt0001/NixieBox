// See SetupX_Template.h for all options available


#define ILI9341_DRIVER
#define TFT_CS    15    // Chip select control pin D15
#define TFT_RST   4     // Reset pin (could connect to NodeMCU RST, see next line)
#define TFT_DC    2     // Data Command control pin D02
#define TFT_MOSI  23    // Chip select control pin D23
#define TFT_SCLK  18    // Chip select control pin D18
#define TFT_BL    17    // BACKLIGHT (LED)
#define TFT_MISO  19    // Chip select control pin D19  
#define TOUCH_CS  21    // Touch Screen CS PIN

// The ESP32 and TFT the pins used for testing are:
//#define TFT_CS   33  // Chip select control pin (library pulls permanently low
//#define TFT_DC   15  // Data Command control pin - must use a pin in the range 0-31
//#define TFT_RST  32  // Reset pin, toggles on startup
//#define TFT_WR    4  // Write strobe control pin - must use a pin in the range 0-31
//#define TFT_RD    2  // Read strobe control pin
//#define TFT_D0   12  // Must use pins in the range 0-31 for the data bus
//#define TFT_D1   13  // so a single register write sets/clears all bits.
//#define TFT_D2   26  // Pins can be randomly assigned, this does not affect
//#define TFT_D3   25  // TFT screen update performance.
//#define TFT_D4   17
//#define TFT_D5   16
//#define TFT_D6   27
//#define TFT_D7   14
//##define SPI_FREQUENCY  40000000

// TFT_3.3V 1     ->    3V3   GREY
// TFT_GND  2     ->    GND   PURPLE
// TFT_CS   3     ->    15    BLUE
// TFT_RST  4     ->    4     GREEN 
// TFT_DC   5     ->    2     YELLOW
// TFT_MOSI 6     ->    23    ORANGE
// TFT_SCLK 7     ->    18    RED
// TFT_LED  8     ->    17    GREY2  (BACKLIGHT)
// TFT_MISO 9     ->    19    YELLOW2


//; | Display      | PIN | E32-P | color | Function            |
//; | ------------ | --- | ----- | ----- | ------------------- |
//; | 3.3     	   | 1   | 3.3   |   |
//; | GND     	   | 2   | GND   |   |
//; | CS (CSX)     | 3   | 15    | 	 | Chip Select(Active Low)
//; | RST          | 4   | 4     |   |
//; | D/C (WR,CX)  | 5   | 2     |   |      
//; | MOSI (SDI)   | 6   | 23    |   |
//; | SCLK (SCL,RS)| 7   | 18    |   |
//; | LED (BL)	   | 8   | 17    |   |
//; | MISO (SDO)   | 9   | 19    |   |
//; | T-CLK	       | 10  |       |	 |
//; | T-CS         | 11  |       |	 |
//; | T-DIN        | 12  |       |	 |    
//; | T-OUT        | 13  |       |	 |    
//; | T-IRQ        | 14  |       |	 |    


// #define CS_PIN  8
// #define TFT_DC  9
// #define TFT_CS 10
// MOSI=11, MISO=12, SCK=13

// #define TIRQ_PIN  2
// XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
// XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
// XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

//#include <ILI9341_t3.h>
//#include <font_Arial.h> // from ILI9341_t3
//#include <XPT2046_Touchscreen.h>
//#include <SPI.h>
// XPT2046_Touchscreen ts(CS_PIN);
// ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

#define TFT_HEIGHT 240
#define TFT_WIDTH  320 
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
//#define SPI_FREQUENCY  27000000
#define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  80000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
#define SUPPORT_TRANSACTIONS
