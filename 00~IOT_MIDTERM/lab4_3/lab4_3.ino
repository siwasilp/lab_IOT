int i, j, k, l, n = 0;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available()) {
    n = Serial.parseInt();  // j is horizontal
    //Serial.print("n = "); // i is vartical
    //Serial.println(n);
    for (i = n-1; i >=0; i--) {
      Serial.println();
      for (l = n - i; l >= 0; l--) {
        Serial.print(" ");
      }
      for (j = 0; j <= 2 * i; j++) {
        if (j % 2 == 0) {
          Serial.print(1);
        }
        if (j % 2 == 1) {
          Serial.print(0);
        }
      }

    }

  }
}
