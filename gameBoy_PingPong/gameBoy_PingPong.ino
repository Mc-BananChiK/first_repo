#include <GyverOLED.h>
#include <SPI.h>
#include <Wire.h>

#define CS  9
#define DS  8
#define RST 7

GyverOLED<SSD1306_128x64, OLED_BUFFER, OLED_SPI, CS, DS, RST> oled;


class PingPong {
  private:
    int x, y, w, h, del, radius, S, Cy0, Cy1 ,Cy2;

  public:
    PingPong(int w, int h, int radius, int del) {
      this->del = del;
      this->w = w;
      this->h = h;
      this->radius = radius;
      x = w / 2;
      y = h / 2;
      S = 1;
    }

    bool newCoordinate() {
      if (S == 1) {
        for (int X = radius; X < w - radius; X++) if (y == radius && x == X) S = 4; // для s = 1
        for (int Y = radius; Y < h - radius; Y++) if (x == radius && y == Y) S = 2;
      }

      if (S == 2) {
        for (int X = radius; X < w - radius; X++) if (y == radius && x == X) S = 3; // для s = 2
        for (int Y = radius; Y < h - radius; Y++) if (x == 127-radius && y == Y) S = 1;
      }

      if (S == 3) {
        for (int X = radius; X < w - radius; X++) if (y == 63-radius && x == X) S = 2; // для s = 3
        for (int Y = radius; Y < h - radius; Y++) if (x == 127-radius && y == Y) S = 4;
      }

      if (S == 4) {
        for (int X = radius; X < w - radius; X++) if (y == 63-radius && x == X) S = 1; // для s = 4
        for (int Y = radius; Y < h - radius; Y++) if (x == radius && y == Y) S = 3;
      }

      if (S == 1) {
        x--;
        y--;
      }
      if (S == 2) {
        x++;
        y--;
      }
      if (S == 3) {
        x++;
        y++;
      }
      if (S == 4) {
        x--;
        y++;
      }
    }

    void drawPole(){
      oled.fastLineH(0, 0, 127, OLED_FILL);
      oled.fastLineH(63, 0, 127, OLED_FILL);
      oled.fastLineV(0, 0, 63, OLED_FILL);
      oled.fastLineV(127, 0, 63, OLED_FILL);
    }

    void drawJoystick(){
      Cy0 = analogRead(A0);
      Cy1 = map(Cy0, 0, 1023, 3, 45);
      Cy2 = map(Cy0, 0, 1023, 3, 45);
      oled.fastLineV(3, Cy1, Cy1+15, OLED_FILL);
      oled.fastLineV(124, Cy2, Cy2+15, OLED_FILL);
    }
    
    void show() {
      oled.clear();
      drawPole();
      drawJoystick();
      oled.circle(x, y, radius, OLED_FILL);
      oled.update();
      delay(del);
    }
};

void setup() {
  Serial.begin(9600);
  oled.init();
  oled.clear();
  oled.home();
  oled.update();
  
  PingPong p(128, 64, 3, 25);

  while (true) {
    p.newCoordinate();
    p.show();
  }
}

void loop() {}
