#ifndef __LOADINGSCREEN._H__
#define __LOADINGSCREEN._H__

#include "Fonts/GFXFF/FreeSans9pt7b.h"
#include "Fonts/GFXFF/FreeSans12pt7b.h"
#include "Fonts/FreeSerif12pt7b.h"

#define PI 3.1415926535897932384626433832795

class LoadingScreen {

private:
      int col[8];
      int16_t x1, y1;
      uint16_t wid, ht;


public:

      LoadingScreen::LoadingScreen() {
            tft.reset();
            Serial.begin(9600);
            uint16_t ID = tft.readID();
            tft.begin(ID);
            tft.setRotation(1);
            tft.invertDisplay(true);
            tft.fillScreen(0xffff);
            showmsgXY(170, 250, 2, &FreeSans9pt7b, "Loading...");
            col[0] = tft.color565(155, 0, 50);
            col[1] = tft.color565(170, 30, 80);
            col[2] = tft.color565(195, 60, 110);
            col[3] = tft.color565(215, 90, 140);
            col[4] = tft.color565(230, 120, 170);
            col[5] = tft.color565(250, 150, 200);
            col[6] = tft.color565(255, 180, 220);
            col[7] = tft.color565(255, 210, 240);
            }

      void LoadingScreen::showmsgXY(int x, int y, int sz, const GFXfont* f, const char* msg)
            {
            tft.setFont(f);
            tft.setCursor(x, y);
            tft.setTextColor(0x0000);
            tft.setTextSize(sz);
            tft.print(msg);
            }

      void LoadingScreen::handler() {
            for (int i = 8; i > 0; i--) {
                  tft.fillCircle(240 + 40 * (cos(-i * PI / 4)), 120 + 40 * (sin(-i * PI / 4)), 10, col[0]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 1) * PI / 4)), 120 + 40 * (sin(-(i + 1) * PI / 4)), 10, col[1]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 2) * PI / 4)), 120 + 40 * (sin(-(i + 2) * PI / 4)), 10, col[2]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 3) * PI / 4)), 120 + 40 * (sin(-(i + 3) * PI / 4)), 10, col[3]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 4) * PI / 4)), 120 + 40 * (sin(-(i + 4) * PI / 4)), 10, col[4]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 5) * PI / 4)), 120 + 40 * (sin(-(i + 5) * PI / 4)), 10, col[5]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 6) * PI / 4)), 120 + 40 * (sin(-(i + 6) * PI / 4)), 10, col[6]);
                  delay(15);
                  tft.fillCircle(240 + 40 * (cos(-(i + 7) * PI / 4)), 120 + 40 * (sin(-(i + 7) * PI / 4)), 10, col[7]);
                  delay(15);
                  }
            }
      }
#endif // __LOADINGSCREEN._H__