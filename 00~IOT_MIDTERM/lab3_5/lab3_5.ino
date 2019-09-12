#include "LedControl.h"


LedControl lc = LedControl(19, 5, 18, 1);
float fe = 3;
float tot;
float me = 3;
float y;
float n;
int i;
void setup() {
  Serial.begin(9600);
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
}

void loop() {
  if (Serial.available())
  {
    n = Serial.parseFloat();
    //n = y*3;
    for (i = 1; i <= n; i++)
    {
      fe = ((fe * 3) + fe) ;
      me = ((me * 3) + (me));
      tot = fe + me;

      Serial.print("term ");
      Serial.println(i);

      Serial.print("female = ");
      Serial.println(fe);

      Serial.print("totol = ");
      Serial.println(tot);
      Serial.println(" ");
    }
    fe = 3;

    me = 3;

  }
  int x = tot;
  lc.setDigit(0, 0, x % 10, false); x = x / 10;
  lc.setDigit(0, 1, x % 10, false); x = x / 10;
  lc.setDigit(0, 2, x % 10, false); x = x / 10;
  lc.setDigit(0, 3, x % 10, false); x = x / 10;
  lc.setDigit(0, 4, x % 10, false); x = x / 10;
  lc.setDigit(0, 5, x % 10, false); x = x / 10;
  lc.setDigit(0, 6, x % 10, false); x = x / 10;
  lc.setDigit(0, 7, x, false);
}
