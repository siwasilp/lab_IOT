#include "LedControl.h"
LedControl lc = LedControl(19, 18, 5, 1);

unsigned long delaytime = 250;
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
}
bool h = false;

void loop() {
  int x = 0;
  while (x <= 100 && !h) {
    lc.setDigit(0, 2, x /100, false);
    lc.setDigit(0, 1, (x%100)/10 , false);
    lc.setDigit(0, 0, x % 10, false);
    x += 3;
    if(x>100)
      h = true;
    delay(200);
  }
}
