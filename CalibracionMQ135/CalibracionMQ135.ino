#include "MQ135.h"
#include <Time.h>

void setup (){
  Serial.begin (9600);
  setTime(9, 24, 0, 4, 10, 2017);
}
void loop() {
  MQ135 gasSensor = MQ135(A0); // Attach sensor to pin A0
  float rzero = gasSensor.getRZero();
  char buffer[20];
  sprintf(buffer,"%02d/%02d/%02d %02d:%02d:%02d,",day(),month(),year(),hour(),minute(),second());

  Serial.print(buffer);
  Serial.println (rzero);
  delay(1000);
}
