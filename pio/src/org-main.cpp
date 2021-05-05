// #include <iostream>
// #include <vector>
// #include <cctype>
// #include <string>
// #include <sstream>
// #include <time.h>
// #include <../lib/TFT_eSPI-2.4.0-Beta/TFT_eSPI.h>
// #include <SPI.h>
// #include <TJpg_Decoder.h>
// #include <SPIFFS.h>
// #include <Wire.h>
// #include <esp_now.h>
// #include <ESPNOW_Manager.h>
// #include <UtilityManager.h>
// #include <Pangodream_18650_CL.h>
// #include "helper/walk.h"
// #include <AnalogButtons.h>
// #include <Button2.h>
// #include <lvgl.h>
// #include <lv_examples.h>

// //#include <GamePadManager.h>
// //#include <BreakOutGame.h>
// #define NB_ICON_WIDTH 31
// #define NB_ICON_HEIGHT 16
// #define NB_STATUS_HEIGHT_BAR NB_ICON_HEIGHT
// #define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
// #define NB_ICON_POS_X (tft.width() - NB_ICON_WIDTH)

// #define MIN_USB_VOL     4.9
// #define ADC_PIN         39
// #define CONV_FACTOR     1.8
// #define READS           20

// char* batteryImages[] = { "/battery_01.jpg", "/battery_02.jpg", "/battery_03.jpg", "/battery_04.jpg", "/battery_05.jpg" };

// /////////////////////////////////////////////////////////////////
// // GPIO DEFINITIONS
// /////////////////////////////////////////////////////////////////[]
// const gpio_num_t sleepPin = GPIO_NUM_33;
// const gpio_num_t batteryPin = GPIO_NUM_39;
// const gpio_num_t buttonPin = GPIO_NUM_35;
// const gpio_num_t wakePin = GPIO_NUM_0;

// #define SLEEP_GPIO_PIN  sleepPin
// #define BATTERY_GPIO_PIN  batteryPin
// #define BUTTON_GPIO_PIN  buttonPin
// #define WAKE_GPIO_PIN  wakePin
// #define TOUCH_CS       21
// //#define TIRQ_PIN       2

// /////////////////////////////////////////////////////////////////
// // CONCRETE CLASSSES
// /////////////////////////////////////////////////////////////////
// TFT_eSPI tft = TFT_eSPI();
// UtilityManager uMan = UtilityManager();
// ESPNOW_Manager esp_now = ESPNOW_Manager();
// AnalogButtons analogButtons = AnalogButtons(BUTTON_GPIO_PIN, INPUT, 5, 100);
// Pangodream_18650_CL BL(ADC_PIN, CONV_FACTOR, READS);

// //XPT2046_Touchscreen ts(TFT_CS, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

// //GamePadManager gamePad = GamePadManager(buttonPin);
// //BreakOutGame breakout = BreakOutGame();
// //digitalRainAnim.init(&tft, 3, 20, 3, 20, 60);

// /////////////////////////////////////////////////////////////////
// // GLOVAL VARIABLES
// ///////////////////////////////////////////////////////////////

// int32_t answer = 0;
// char lastchar = ' ';
// char keyarray1[200];
// char keyarray2[200];
// int32_t keyarray1i = 0;
// int32_t keyarray2i = 0;
// char operation = ' ';
// long Time = 0;
// long millicount = 0;
// int interval = 1000;
// int screenTimout = 15;
// int32_t extray = 43;
// int32_t x, y = 0;
// int imgNum = 0;

// int margin = 20;
// int _currentPage = 0;
// int lastPage = 0;
// int _delay = 3000;

// int _currentScreen = 0;
// int _numScreens = 6;
// int _maxScreen = _numScreens - 1;

// /////////////////////////////////////////////////////////////////
// // DISPLAY METHODS
// ///////////////////////////////////////////////////////////////

// bool DEBUG_ON = false;
// bool SHOW_HEADER = true;
// bool SHOW_BOOT_SCREEN = true;
// bool SHOW_BATTERY_DETAILS = false;
// int StatusBarX = 0;


// bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
//       // Stop further decoding as image is running off bottom of screen
//       if (y >= tft.height()) return 0;
//       // This function will clip the image block rendering automatically at the TFT boundaries
//       tft.pushImage(x, y, w, h, bitmap);
//       // Return 1 to decode next block
//       return 1;
//       }

// void displayInit() {

//       tft.begin();
//       tft.setRotation(3);
//       tft.fillScreen(TFT_BLACK);
//       tft.setTextSize(2);
//       TJpgDec.setJpgScale(1);
//       tft.setSwapBytes(true);
//       TJpgDec.setCallback(tft_output);
//       }

// void drawingBatteryIcon(String filePath) {
//       TJpgDec.drawFsJpg(NB_ICON_POS_X, 0, filePath);
//       }

// void drawBatteryText(String text) {
//       //tft.fillRect(0, 0, ICON_POS_X, ICON_HEIGHT, TFT_BLACK);
//       tft.setTextDatum(2);
//       tft.drawString(text, NB_ICON_POS_X - 2, NB_STATUS_HEIGHT_BAR / 2, 2);
//       }

// void drawRectCenterdText(String text) {
//       tft.fillRect(0, 0, NB_ICON_POS_X, NB_ICON_HEIGHT, TFT_BLACK);
//       tft.setTextDatum(2);
//       tft.drawString(text, NB_ICON_POS_X - 2, NB_STATUS_HEIGHT_BAR / 2, 2);
//       }

// void drawRectText(String text, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t fontColor) {
//       tft.fillRect(x, y, w, h, fontColor);
//       tft.drawString(text, x, y);
//       }

// // // Highlights the button when pressed
// void drawFrame(int x1, int y1, int x2, int y2) {
//       tft.fillRect(x1, y1, x2, y2, TFT_RED);
//       tft.drawRoundRect(x1, y1, x2, y2, 20, TFT_SILVER);
//       }


// #define minpressure 10
// #define maxpressure 1000
// #define row1x 0
// #define box1y 260
// #define boxsize 60
// #define r1x 190
// #define b1y 55


// void showSystemPrefs() {
//       drawRectCenterdText("Coming Soon!");
//       drawRectCenterdText("Returning To Home Screen");
//       delay(500);
//       }

// #define BOOT_INTERVALS        3000       	// show boot screen for 10 sec
// #define BOOT_LOOPS            5
// #define BOOT_FRAMES           23          //  Number of frames in boot menu

// // Show Boot Screen
// void showBootScreen() {
//       for (int y = 0; y <= 3;y++) {
//             for (int x = 0; x <= 23;x++) {
//                   String imgPath = "/image_";
//                   imgPath += (String)x;
//                   imgPath += ".jpg";
//                   TJpgDec.drawFsJpg(0, 0, imgPath);
//                   delay(30);
//                   }
//             }
//       }

// #define MAIL_ICON_FRAMES  45  //  Number of Mail_ICON_FRAMES

// void showMailDrop() {

//       for (int x = 0; x <= 45;x++) {
//             String imgPath = (x > 10 ? "/00" + (String)x : "/0" + (String)x);
//             //imgPath += (String)x;
//             imgPath += ".jpg";
//             TJpgDec.drawFsJpg(0, 0, imgPath);
//             delay(20);
//             }
//       }

// // Update The display every 24 ms
// void showTopBar() {

//       tft.setCursor(0, 0);
//       // Vout = (4.2*100k)/(27k + 100k) = 3.3V // // VOLTAGE DIVIDER FOR REDUCED CONSUMPTION AND MEASURMENTS
//       // float batteryLevel = map(analogRead(batteryPin), 0.00f, 4095.00f, 0.00f, 100.00f);
//       int batteryLevel = BL.getBatteryChargeLevel();

//       if (SHOW_BATTERY_DETAILS) {
//             tft.println("");
//             tft.print("Average value from pin: ");
//             tft.println(BL.pinRead());
//             tft.print("Volts: ");
//             tft.println(BL.getBatteryVolts());
//             tft.print("Charge level: ");
//             tft.println(BL.getBatteryChargeLevel());
//             }

//       if (BL.getBatteryVolts() <= MIN_USB_VOL) {
//             (imgNum < ARRAY_SIZE(batteryImages) ? imgNum++ : imgNum = 4);
//             }
//       else {
//             if (batteryLevel >= 80) imgNum = 3;
//             else if (batteryLevel < 80 && batteryLevel >= 50) imgNum = 2;
//             else if (batteryLevel < 50 && batteryLevel >= 20) imgNum = 1;
//             else if (batteryLevel < 20) imgNum = 0;
//             else imgNum = 4;
//             }

//       // Set Time Properly
//       String min = (String)uMan.getNow().minute();
//       if (min.length() == 1) { min = "0" + min; }

//       drawingBatteryIcon(batteryImages[imgNum]);
//       tft.setCursor((tft.width() - 56), 0);
//       tft.print(String(batteryLevel) + "%");
//       tft.setCursor(5, 0);
//       tft.print((String)uMan.getNow().twelveHour() + ":" + min);

//       }

// int dotCount = 0;

// void showChatScreen() {

//       // SET STARTING POINT
//       tft.setCursor(0, 40);
//       tft.setCursor(tft.getCursorX(), tft.getCursorY() + 10);
//       tft.setTextDatum(2);
//       tft.println(" ");
//       tft.println(" ");
//       tft.println("         Nixie Chat");
//       tft.println("     " + WiFi.macAddress());
//       tft.print("    Members Online: ");

//       // TODO: Implement member Count
//  //     uint8_t esp_now.MemberCount;
//  //     WiFi.softAPgetStationNum();
//  //     tft.println(esp_now.MemberCount);

//       tft.println(" ");
//       tft.print("  waiting");

//       // TDDO: MOVE
//       // DOT... EFFECT
//       if (dotCount >= 4) {
//             dotCount = 0;
//             tft.print("       ");
//             tft.setCursor(tft.getCursorX(), 0);
//             }

//       for (int x = 1;x <= dotCount;x++) { tft.print("."); }
//       dotCount++;

//       if (esp_now.hasUnreadMail()) {
//             showMailDrop();
//             esp_now.mailRead();
//             }
//       }

// int x1 = 10;
// int x2 = 40;
// int yCenter = tft.height() / 2;
// int xCenter = tft.width() / 2;

// int btnCount = 10; // ARRBRATRARY
// int edgePadding = 5; // L&R COMBINED
// int bSpacing = 10;
// int bHeight = 80;
// int bWidth = 80;
// int bSize = bWidth + bSpacing;
// int bPerRow = (tft.width() / (bSize + edgePadding * 2));
// int rowBtnCount = btnCount / bPerRow;

// // //int bXY[rowBtnCount][bPerRow];
// // int** ary = new int* [sizeY];
// // for (int i = 0; i < sizeY; ++i) {
// //       ary[i] = new int[sizeX];
// //       }

// int bXcenter = x2 - x1;
// int rowIconCount = 4;
// int colIconCount = 1;

// //SimpleList buttonList = SimpleList();
// //buttonList.add("1");


// template<class Data>
// class List
//       {
//       struct Cell {
//             Data data;
//             Cell* next;
//             };
//       };

// void drawHomeScreen() {

//       // DRAW NIXIE CHAT
//       tft.setTextDatum(0);
//       int x1c = (tft.getCursorX() / colIconCount);
//       int y1c = (tft.getCursorX() / rowIconCount);
//       tft.drawRoundRect(x1c, y1c, bWidth, bHeight, 10, TFT_BLUE);
//       tft.fillRoundRect(x1c, y1c, bWidth, bHeight, 5, TFT_SKYBLUE);
//       tft.println("Nixie CHAT"); // Prints the string

//      // DRAW NIXIE BIRD
//       tft.setTextDatum(0);
//       tft.drawRoundRect(x1c * 2, y1c, bWidth, bHeight, 10, TFT_GREEN);
//       tft.fillRoundRect(x1c * 2, y1c, bWidth, bHeight, 5, TFT_GREENYELLOW);
//       tft.setCursor(tft.getCursorX(), tft.getCursorY() + 20);
//       tft.println("Nixie Bird"); // Prints the string

//      // DRAW Shapes        
//       tft.drawRoundRect(x1c * 3, y1c, bWidth, bHeight, 10, TFT_VIOLET);
//       tft.fillRoundRect(x1c * 3, y1c, bWidth, bHeight, 5, TFT_OLIVE);
//       tft.setCursor(tft.getCursorX(), tft.getCursorY() + 20);
//       tft.println("Draw SHapes"); // Prints the string

//      // DRAW Mail
//       tft.drawRoundRect(x1c * 4, y1c, bWidth, bHeight, 10, TFT_ORANGE);
//       tft.fillRoundRect(x1c * 4, y1c, bWidth, bHeight, 5, TFT_YELLOW);
//       tft.setCursor(tft.getCursorX(), tft.getCursorY() + 20);
//       tft.println("Check Mail"); // Prints the string

//       }

// #define YP A3
// #define XM A2
// #define YM 9 
// #define XP 8  
// #define BOXSIZE 40
// #define PENRADIUS 3

// int oldcolor, currentcolor, sc, v = 0, pv = 0, i = 0, j = 0;
// float a = 0.5;

// ///////////////////////////////////////////////////////////////
// //  BIRD GAME
// ///////////////////////////////////////////////////////////////

// void bird(int n) {
//       tft.fillCircle(tft.width() / 3, tft.height() / 2 - 45 + v, 18, TFT_YELLOW);
//       tft.drawCircle(tft.width() / 3, tft.height() / 2 - 45 + v, 18, TFT_BLACK);
//       tft.fillRect(tft.width() / 3, tft.height() / 2 - 40 + v, 20, 7, TFT_RED);
//       tft.drawRect(tft.width() / 3, tft.height() / 2 - 40 + v, 20, 7, TFT_BLACK);
//       tft.fillRect(tft.width() / 3, tft.height() / 2 - 37 + v, 20, 1, TFT_BLACK);
//       tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + v, 7, TFT_WHITE);
//       tft.drawCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + v, 7, TFT_BLACK);
//       tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + v, 2, TFT_BLACK);
//       tft.fillRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + v, 18, 7, TFT_WHITE);
//       tft.drawRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + v, 18, 7, TFT_BLACK);
//       }

// void birdcyan(int pv)
//       {
//       tft.fillCircle(tft.width() / 3, tft.height() / 2 - 45 + pv, 18, TFT_CYAN);
//       tft.drawCircle(tft.width() / 3, tft.height() / 2 - 45 + pv, 18, TFT_CYAN);
//       tft.fillRect(tft.width() / 3, tft.height() / 2 - 40 + pv, 20, 7, TFT_CYAN);
//       tft.drawRect(tft.width() / 3, tft.height() / 2 - 40 + pv, 20, 7, TFT_CYAN);
//       tft.fillRect(tft.width() / 3, tft.height() / 2 - 37 + pv, 20, 1, TFT_CYAN);
//       tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + pv, 7, TFT_CYAN);
//       tft.drawCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + pv, 7, TFT_CYAN);
//       tft.fillCircle(tft.width() / 3 + 7, tft.height() / 2 - 54 + pv, 2, TFT_CYAN);
//       tft.fillRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + pv, 18, 7, TFT_CYAN);
//       tft.drawRect(tft.width() / 3 - 23, tft.height() / 2 - 45 + pv, 18, 7, TFT_CYAN);
//       }

// void drawBirdGame() {

//       Serial.println(F("Bird!"));
//       tft.fillScreen(TFT_CYAN);
//       bird(0);
//       tft.fillRect(0, 20, tft.width(), 3, TFT_BLACK);
//       tft.fillRect(0, 0, tft.width(), 20, 0xD78A);
//       tft.setTextSize(2);
//       tft.setCursor(tft.width() / 3 - 10, 0);
//       tft.setTextColor(TFT_RED);
//       tft.print("Score :");
//       tft.print(sc);

//       tft.fillRect(0, tft.height() - 33, tft.width(), 8, 0x3F30);
//       tft.fillRect(0, tft.height() - 25, tft.width(), 25, 0xD78A);
//       tft.setCursor(60, tft.height() - 20);
//       tft.setTextColor(TFT_BLUE);
//       tft.print("NIXIE BIRD");

//       tft.setCursor(30, 135);
//       tft.setTextColor(0xF080);
//       tft.setTextSize(4);
//       tft.print("HOLD SELECT TO PLAY");
//       }

// void startBirdGame() {
//       tft.fillScreen(TFT_CYAN);
//       tft.fillRect(0, 0, tft.width(), 20, 0xD78A);
//       tft.fillRect(0, tft.height() - 25, tft.width(), 25, 0xD78A);
//       bird(0);

//       tft.fillRect(tft.width() - 40 - (i * 2), 20, 20, 50, 0xD78A);
//       tft.fillRect(tft.width() - 40 - (i * 2), 165, 20, 50, 0xD78A);
//       tft.fillRect(tft.width() - 20 - (i * 2), 20, 20, 50, TFT_CYAN);
//       tft.fillRect(tft.width() - 20 - (i * 2), 165, 20, 50, TFT_CYAN);

//       //delay(1);
//       tft.fillRect(0, 0, 20, tft.height(), 0xD78A);
//       pv = v;
//       v = v + (4 * a * j);
//       birdcyan(pv);
//       bird(v);
//       j++;
//       i++;

//       Serial.println(v);
//       if (i == 141 && (v <= 120 || v > -34 || (280 - (2 * i) < 106 && 280 - (2 * i) > 70 && 57 + v > 73 && 93 + v < 165)))
//             i = 0;
//       else if ((v >= 122 || v < (-34) || ((280 - (2 * i) < 106) && (280 - (2 * i) > 70) && ((57 + v < 73) || (93 + v > 165)) && i < 143)))
//             {
//             tft.fillScreen(TFT_CYAN);
//             // tft.setCursor((tft.width() / 3 + 36), W_CENTER);
//             tft.setTextSize(3);
//             tft.println("GAME OVER");
//             Serial.println("Game over");
//             i = 500;
//             }
//       else {}//a=0.4;
//       //}

//       }

// void drawShapes() {
//       int w = tft.width();
//       int h = tft.height();

//       Serial.println("Draw a rectangle");
//       tft.fillScreen(TFT_BLACK);
//       tft.drawRect(margin, margin, w - (2 * margin), h - (2 * margin), TFT_RED);
//       delay(_delay);

//       Serial.println("Draw a filled rectangle");
//       // fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
//       tft.fillRect(2 * margin, 2 * margin, w - (4 * margin), h - (4 * margin), TFT_VIOLET);
//       delay(_delay);

//       Serial.println("Draw a rounded corner rectangle outline");
//       //drawRoundRect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, uint32_t color)
//       tft.drawRoundRect(3 * margin, 3 * margin, w - (6 * margin), h - (6 * margin), 8, TFT_YELLOW);
//       delay(_delay);

//       Serial.println("Draw a line");
//       // drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint32_t color)
//       tft.drawLine(0, 0, w, h, TFT_DARKGREY);
//       delay(_delay);

//       _currentPage = 0;
//       }


// /////////////////////////////////////////////////////////////////
// // MENU HANDLER
// ///////////////////////////////////////////////////////////////

// // void processMenu() {

// //       if (menuManager.getScreen < 0) {
// //             tft.setCursor(0, 0);
// //             tft.print(screens[0][0]);
// //             tft.print(": ");
// //             tft.print(parameters[0]);
// //             tft.print(" ");
// //             tft.print(screens[0][1]);

// //             tft.setCursor(0, 1);
// //             tft.print(screens[1][0]);
// //             tft.print(": ");
// //             tft.print(parameters[1]);
// //             tft.print(" ");
// //             tft.print(screens[1][1]);

// //             tft.setCursor(0, 2);
// //             tft.print(screens[2][0]);
// //             tft.print(": ");
// //             tft.print(parameters[2]);
// //             tft.print(" ");
// //             tft.print(screens[2][1]);

// //             tft.setCursor(0, 3);
// //             tft.print(screens[3][0]);
// //             tft.print(": ");
// //             tft.print(parameters[3]);
// //             tft.print(" ");
// //             tft.print(screens[3][1]);
// //             }
// //       else {
// //             tft.setCursor(0, 0);
// //             tft.print("MENU TOTORIAL");
// //             tft.setCursor(0, 2);
// //             tft.print(screens[_currentScreen][0]);
// //             tft.setCursor(0, 3);
// //             tft.print(parameters[_currentScreen]);
// //             tft.print(" ");
// //             tft.print(screens[_currentScreen][1]);
// //             }

//       /////////////////////////////////////////////////////////////////
//       // BUTTON HANDLER
//       ///////////////////////////////////////////////////////////////

// //       // int _currentScreen = 0;
// //       // int _numScreens = 5;
// //       // int _maxScreen = _numScreens - 1;

// void processMenu(int _pressedButtonNumber, bool wasHeld = false) {

//       //if (lastButtonPressed == _buttonPressed) 
//             //break;

//       switch (_pressedButtonNumber) {
//                   case 1:
//                         _currentScreen--;
//                         break;
//                   case 3:
//                         _currentScreen++;
//                         break;
//                   case 5:
//                         //startAPP();
//                         break;
//             }

//       if (_currentScreen < _maxScreen) _currentScreen = 0;
//       if (_currentScreen > 0) _currentScreen = _maxScreen;

//       showChatScreen();
//       }

// // LEFT -   SHOW BOOT
// // UP -     SEND MAIL
// // RIGHT -  Draw Shapes
// // DOWN - 
// // SELECT - BirdGame

// int _pressedButtonNumber = -1;
// bool _buttonPressed = false;

// // left button
// void left_b_Click() {
//       Serial.println("left clicked");
//       _pressedButtonNumber = 0;
//       switch (_currentPage) {
//                   case 0:
//                         //drawChatScreen();
//                         //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       }
// void left_b_Hold() {
//       Serial.println("left held");
//       _pressedButtonNumber = 0; _buttonPressed = true;

//       switch (_currentPage) {
//                   case 0:
//                         //drawChatScreen();
//                         //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       //showBootScreen();
//       }

// // SEND MAIL
// // up_b_ = UpButton
// void up_btn_Click() {
//       Serial.println("up clicked");
//       switch (_currentPage) {
//                   case 0:
//                         //drawChatScreen();
//                         //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       }
// void up_btn_Hold() {
//       Serial.println("up held");
//       _pressedButtonNumber = 1; _buttonPressed = true;
//       switch (_currentPage) {
//                   case 0:
//                         //drawChatScreen();
//                         //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       if (esp_now.hasUnreadMail()) {
//             esp_now.mailReceived();
//             }
//       }

// void right_btn_Click() {
//       Serial.println("right clicked");
//       switch (_currentPage) {
//                   case 0:
//                         processMenu(3);
//                         //drawChatScreen();
//                   //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       }
// void right_btn_Hold() {
//       Serial.println("right held");
//       _pressedButtonNumber = 2; _buttonPressed = true;
//       switch (_currentPage) {
//                   case 0:
//                         //drawChatScreen();
//                         //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       //breakout.initgame();
//       drawShapes();
//       }

// void downt_btn_Click() {
//       switch (_currentPage) {
//                   case 0:
//                         //drawChatScreen();
//                         //showPages();
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       }

// void downt_btn_Hold() {
//       Serial.println("down held");
//       _pressedButtonNumber = 3; _buttonPressed = true;
//       switch (_currentPage) {
//                   case 0:
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         break;
//                   case 3:
//                         break;
//             }
//       }

// void select_btn_Click() {
//       Serial.println("select clicked");
//       switch (_currentPage) {

//                   case 0:
//                         //startApp(_currentPage, lastButtonPressed);
//                         break;
//                   case 1:
//                         showChatScreen();
//                         break;
//                   case 2:
//                         drawBirdGame();
//                         j = -8;
//                         break;
//                   case 3:
//                         drawShapes();
//                         break;
//                   case 4:
//                         break;
//                   case 5:
//                         showSystemPrefs();
//                         break;
//             }
//       }
// void select_btn_Hold() {
//       Serial.println("select held");
//       _pressedButtonNumber = 4; _buttonPressed = true;

//       if (_pressedButtonNumber == 4 && _buttonPressed) {
//             drawHomeScreen();
//             }

//       switch (_currentPage) {
//                   case 0:
//                         break;
//                   case 1:
//                         break;
//                   case 2:
//                         startBirdGame();
//                         break;
//                   case 3:
//                         break;
//             }
//       }

// /////////////////////////////////////////////////////////////////
// // POWER METHODS
// ///////////////////////////////////////////////////////////////

// void pinoutInit() {
//       pinMode(ADC_PIN, OUTPUT);
//       digitalWrite(ADC_PIN, HIGH);
//       }

// void SPIFFSInit() {
//       if (!SPIFFS.begin()) {
//             Serial.println("SPIFFS initialisation failed!");
//             while (1) yield(); // Stay here twiddling thumbs waiting
//             }
//       Serial.println("\r\nSPIFFS Initialisation done.");
//       }

// void ListSPIFFS() {
//       Serial.println(F("\r\nListing SPIFFS files:"));
//       static const char line[] PROGMEM = "=================================================";

//       Serial.println(FPSTR(line));
//       Serial.println(F("  File name                              Size"));
//       Serial.println(FPSTR(line));

//       fs::File root = SPIFFS.open("/");
//       if (!root) {
//             Serial.println(F("Failed to open directory"));
//             return;
//             }
//       if (!root.isDirectory()) {
//             Serial.println(F("Not a directory"));
//             return;
//             }

//       fs::File file = root.openNextFile();
//       while (file) {

//             if (file.isDirectory()) {
//                   Serial.print("DIR : ");
//                   String fileName = file.name();
//                   Serial.print(fileName);
//                   }
//             else {
//                   String fileName = file.name();
//                   Serial.print("  " + fileName);
//                   // File path can be 31 characters maximum in SPIFFS
//                   int spaces = 33 - fileName.length(); // Tabulate nicely
//                   if (spaces < 1) spaces = 1;
//                   while (spaces--) Serial.print(" ");
//                   String fileSize = (String)file.size();
//                   spaces = 10 - fileSize.length(); // Tabulate nicely
//                   if (spaces < 1) spaces = 1;
//                   while (spaces--) Serial.print(" ");
//                   Serial.println(fileSize + " bytes");
//                   }

//             file = root.openNextFile();
//             }

//       Serial.println(FPSTR(line));
//       Serial.println();
//       delay(1000);
//       }

// /////////////////////////////////////////////////////////////////
// // CORE MANAGER
// ///////////////////////////////////////////////////////////////

// TaskHandle_t DisplayTask;
// TaskHandle_t MemberTask;
// TaskHandle_t MenuTask;

// // TIMING OF EVENTS
// #define DISPLAY_INTERVAL      300			// Update display every 24 ms... (30 fps)
// #define WAIT_BOOT_DURATION    5000    		// show boot screen for 5 sec
// #define MEMBER_INTERVAL       30000      		// Look for members every 30 seconds

// void DisplayHandler(void* pvParameters) {
//       Serial.print("DisplayHandler running on core ");
//       //Serial.println(xPortGetCoreID());
//       //vTaskDelay(WAIT_BOOT_DURATION);
//       for (;;) {
//             showTopBar();
//             showChatScreen();
//             vTaskDelay(DISPLAY_INTERVAL);
//             }
//       }

// // MemberHandler: look for new member every 5 Sec
// void MemeberHandler(void* pvParameters) {
//       Serial.print("Member handler running on core ");
//       Serial.println(xPortGetCoreID());
//       //vTaskDelay(WAIT_BOOT_DURATION);
//       for (;;) {
//             esp_now.ScanForMembers();
//             esp_now.manageMembers();
//             esp_now.EnrolMembers();
//             vTaskDelay(MEMBER_INTERVAL);
//             }
//       }
// void ProcessMenuHandler(void* pvParameters) {
//       Serial.print("DisplayHandler running on core ");
//       Serial.println(xPortGetCoreID());
//       //vTaskDelay(WAIT_BOOT_DURATION);
//       for (;;) {
//             processMenu(-1);
//             vTaskDelay(DISPLAY_INTERVAL);
//             }
//       }

// // Setup FreeRTOS Multicore
// void initCores() {
//       //xTaskCreatePinnedToCore(DisplayHandler, "DisplayHandler", 10000, NULL, 2, &DisplayTask, 0);      // Update Display  
//       xTaskCreatePinnedToCore(MemeberHandler, "MemberTask", 10000, NULL, 3, &MemberTask, 1);          // Scan for members
//       xTaskCreatePinnedToCore(ProcessMenuHandler, "processMenu", 10000, NULL, 1, &MenuTask, 1);      // Update Display        
//       }

// /////////////////////////////////////////////////////////////////
// // MASTER SETUP METHOD
// /////////////////////////////////////////////////////////////////
// void setup() {
//       Serial.begin(115200);

//       Button left_btn = Button(0, &left_b_Click, &left_b_Hold, 1000, 150);                // LEFT = 0
//       Button up_btn = Button(400, &up_btn_Click, &up_btn_Hold, 1000, 150);                // UP = 362 - 446
//       Button down_btn = Button(1150, &downt_btn_Click, &downt_btn_Hold, 1000, 150);       // DOWN = 1199 - 1104
//       Button right_btn = Button(1775, &right_btn_Click, &right_btn_Hold, 1500, 150);      // RIGHT = 1819 - 1758
//       Button select_btn = Button(2620, &select_btn_Click, &select_btn_Hold, 1000, 500);   // SELECT = 2719 - 2666
//       analogButtons.add(left_btn);
//       analogButtons.add(up_btn);
//       analogButtons.add(down_btn);
//       analogButtons.add(right_btn);
//       analogButtons.add(select_btn);

//       pinoutInit();
//       displayInit();
//       SPIFFSInit();
//       ListSPIFFS();
//       uMan.setupWifi();
//       esp_now.initMesh();

//       tft.fillScreen(TFT_BLACK);
//       Serial.println("BootMenu");
//       showBootScreen();
//       // tft.fillScreen(TFT_BLACK);
//       // Serial.println("New Mail");
//       // showMailDrop();
//       // tft.fillScreen(TFT_BLACK);
//       // Serial.println("HomeScreen");
//       // drawHomeScreen();
//       tft.fillScreen(TFT_BLACK);
//       initCores();
//       // drawintro();
//       // draw();
//       }

// void configure() {
//       unsigned int value = analogRead(buttonPin);
//       Serial.println(value);
//       delay(250);
//       }

// /////////////////////////////////////////////////////////////////
// // Main Loop
// /////////////////////////////////////////////////////////////////
// void loop() {

//       //configure();
//       analogButtons.check();
//       showTopBar();
//       showChatScreen();

//       }

// // // Keypad start position, key sizes and spacing
// // #define KEY_X 120 // Center of key
// // #define KEY_Y 170
// // #define KEY_W 70 // Width and height
// // #define KEY_H 30
// // #define KEY_TEXTSIZE 1 // Font size multiplier

// // // Using two fonts since numbers are nice when bold
// // #define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
// // // Create Signal Button
// // char keyLabel[] = "TEST";
// // uint16_t keyColor = TFT_BLUE;
// // // Invoke the TFT_eSPI button class and create all the button objects
// // TFT_eSPI_Button key = TFT_eSPI_Button()
// // // drawHomeScreen - Custom Function

// // void drawKeypad(void) {
// //       // Draw the Button
// //       tft.setFreeFont(LABEL1_FONT);
// //       key.initButton(&tft, // REF - LEAVE AS IS
// //             KEY_X, // X Cord: SEE ABOVE Line 19
// //             KEY_Y, // Y CORD: SEE ABOVE Line 20
// //             KEY_W, // WIDTH: SEE ABOVE Line 21
// //             KEY_H, // HEIGHT: SEE ABOVE Line 22
// //             TFT_WHITE, // OUTLINE
// //             keyColor, // TEXT COLOR
// //             TFT_WHITE, // FILL
// //             keyLabel, // TEXT TO PRINT
// //             KEY_TEXTSIZE); // TEXT SIZE: SEE ABOVE Line 23
// //       key.drawButton();
// //       }

// // void draw() {
// //       tft.fillScreen(TFT_BLACK);

// //       tft.drawRoundRect(row1x, box1y, boxsize, boxsize, 8, RED);
// //       tft.drawRoundRect(row1x, box1y - boxsize, boxsize, boxsize, 8, WHITE);
// //       tft.drawRoundRect(row1x, box1y - boxsize * 2, boxsize, boxsize, 8, WHITE);
// //       tft.drawRoundRect(row1x, box1y - boxsize * 3, boxsize, boxsize, 8, WHITE);

// //       for (int32_t b = box1y; b >= 80; b -= boxsize)
// //             {
// //             tft.drawRoundRect(180, b, boxsize, boxsize, 8, BLUE);
// //             tft.drawRoundRect(row1x + boxsize, b, boxsize, boxsize, 8, WHITE);
// //             }
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y, boxsize, boxsize, 8, GREEN);
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y - boxsize, boxsize, boxsize, 8, WHITE);
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y - boxsize * 2, boxsize, boxsize, 8, WHITE);
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y - boxsize * 3, boxsize, boxsize, 8, WHITE);

// //       for (int32_t j = 0; j < 4; j++) {
// //             for (int32_t i = 0; i < 4; i++) {
// //                   tft.setCursor(22 + (boxsize * i), 100 + (boxsize * j));
// //                   tft.setTextSize(3);
// //                   tft.setTextColor(WHITE);
// //                   tft.println(button[j][i]);
// //                   }
// //             }
// //       tft.drawRoundRect(2, 5, 235, 70, 8, ORANGERED);
// //       }


// // void drawintro()
// //       {
// //       tft.fillScreen(TFT_BLACK);
// //       tft.setTextSize(3);
// //       tft.drawRoundRect(0, 0, 240, 319, 20, TFT_RED);
// //       tft.setTextColor(TFT_BLUE);
// //       tft.setCursor(30, 100);
// //       tft.print("Welcome To");
// //       tft.setCursor(30, 130);
// //       tft.setTextColor(TFT_YELLOW);
// //       tft.print("NotesPoint");
// //       tft.setCursor(30, 160);
// //       tft.setTextColor(TFT_RED);
// //       tft.print("CALCULATOR");
// //       tft.setCursor(45, 250);
// //       tft.setTextColor(TFT_WHITE);
// //       tft.print("Touch To");
// //       tft.setCursor(45, 280);
// //       tft.print("Continue");
// //       tft.setCursor(30, 50);
// //       tft.fillRoundRect(20, 40, 200, 40, 8, TFT_YELLOW);
// //       tft.setTextColor(TFT_RED);
// //       tft.print("NotesPoint");
// //       tft.fillRoundRect(25, 215, 180, 5, 8, TFT_GREEN);

// //       while (i == 1) {
// //             }
// //       }

// // void draw()
// //       {
// //       tft.fillScreen(TFT_BLACK);

// //       tft.drawRoundRect(row1x, box1y, boxsize, boxsize, 8, TFT_RED);
// //       tft.drawRoundRect(row1x, box1y - boxsize, boxsize, boxsize, 8, TFT_WHITE);
// //       tft.drawRoundRect(row1x, box1y - boxsize * 2, boxsize, boxsize, 8, TFT_WHITE);
// //       tft.drawRoundRect(row1x, box1y - boxsize * 3, boxsize, boxsize, 8, TFT_WHITE);

// //       for (int32_t b = box1y; b >= 80; b -= boxsize)
// //             {
// //             tft.drawRoundRect(180, b, boxsize, boxsize, 8, TFT_BLUE);
// //             tft.drawRoundRect(row1x + boxsize, b, boxsize, boxsize, 8, TFT_WHITE);
// //             }

// //       tft.drawRoundRect(row1x + boxsize * 2, box1y, boxsize, boxsize, 8, TFT_GREEN);
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y - boxsize, boxsize, boxsize, 8, TFT_WHITE);
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y - boxsize * 2, boxsize, boxsize, 8, TFT_WHITE);
// //       tft.drawRoundRect(row1x + boxsize * 2, box1y - boxsize * 3, boxsize, boxsize, 8, TFT_WHITE);

// //       for (int32_t j = 0; j < 4; j++) {
// //             for (int32_t i = 0; i < 4; i++) {
// //                   tft.setCursor(22 + (boxsize * i), 100 + (boxsize * j));
// //                   tft.setTextSize(3);
// //                   tft.setTextColor(TFT_WHITE);
// //                   tft.println(button[j][i]);
// //                   }
// //             }
// //       tft.drawRoundRect(2, 5, 235, 70, 8, TFT_ORANGE);
// //       }

// // void drawintro()
// //       {
// //       tft.fillScreen(TFT_BLACK);
// //       tft.setTextSize(3);
// //       tft.drawRoundRect(0, 0, 240, 319, 20, TFT_RED);

// //       tft.setTextColor(TFT_BLUE);
// //       tft.setCursor(30, 100);
// //       tft.print("Welcome To");
// //       tft.setCursor(30, 130);
// //       tft.setTextColor(FT_YELLOW);
// //       tft.print("NotesPoint");
// //       tft.setCursor(30, 160);
// //       tft.setTextColor(FT_RED);
// //       tft.print("CALCULATOR");
// //       tft.setCursor(45, 250);
// //       tft.setTextColor(FT_WHITE);
// //       tft.print("Touch To");
// //       tft.setCursor(45, 280);
// //       tft.print("Continue");
// //       tft.setCursor(30, 50);
// //       tft.fillRoundRect(20, 40, 200, 40, 8, TFT_YELLOW);
// //       tft.setTextColor(RED);
// //       tft.print("NotesPoint");
// //       tft.fillRoundRect(25, 215, 180, 5, 8, TFT_GREEN);
// //       }