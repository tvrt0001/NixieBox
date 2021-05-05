// #ifndef MENUMANAGER_H
// #define MENUMANAGER_H

// #include <../TFT_eSPI-2.4.0-Beta/TFT_eSPI.h>

// class MenuManager {

// private:

// public:

//       TFT_eSPI lcd;
//       // int currentScreen = 0;
//       // int _numScreens = 5;
//       // int _maxScreen = _numScreens - 1;
//       int screen[5] = { 0,1,2,3,4 };

//       ~MenuManager() { };
//       MenuManager(TFT_eSPI& tft) {
//             lcd = &tft;
//             }

//       int getScreen() { return currentScreen; }

//       //  1 	LEFT
//       //  2 	UP
//       //  3 	RIGHT
//       //  4 	DOWN
//       //  5 	SELECT
//       void processMenu(int pButton, bool wasHeld = false) {

//             switch (pButton) {
//                         case 1:
//                               currentScreen--;
//                               break;
//                         case 3:
//                               currentScreen++;
//                               break;
//                         case 5:
//                               break;
//                         default:
//                               currentScreen = 0;
//                               continue;
//                   }

//             if (currentScreen < _maxScreen) currentScreen = 0;
//             if (currentScreen > 0) currentScreen = _maxScreen;
//             }

//       void :printScreen() {
//             if (currentScreen == 0) {
//                   lcd.setCursor(0, 0);
//                   lcd.print(screens[0][0]);
//                   lcd.print(": ");
//                   lcd.print(parameters[0]);
//                   lcd.print(" ");
//                   lcd.print(screens[0][1]);

//                   lcd.setCursor(0, 1);
//                   lcd.print(screens[1][0]);
//                   lcd.print(": ");
//                   lcd.print(parameters[1]);
//                   lcd.print(" ");
//                   lcd.print(screens[1][1]);

//                   lcd.setCursor(0, 2);
//                   lcd.print(screens[2][0]);
//                   lcd.print(": ");
//                   lcd.print(parameters[2]);
//                   lcd.print(" ");
//                   lcd.print(screens[2][1]);

//                   lcd.setCursor(0, 3);
//                   lcd.print(screens[3][0]);
//                   lcd.print(": ");
//                   lcd.print(parameters[3]);
//                   lcd.print(" ");
//                   lcd.print(screens[3][1]);
//                   }
//             else {
//                   lcd.setCursor(0, 0);
//                   lcd.print("MENU TOTORIAL");
//                   lcd.setCursor(0, 2);
//                   lcd.print(screens[currentScreen][0]);
//                   lcd.setCursor(0, 3);
//                   lcd.print(parameters[currentScreen]);
//                   lcd.print(" ");
//                   lcd.print(screens[currentScreen][1]);
//                   }
//             }
//       };
// #endif