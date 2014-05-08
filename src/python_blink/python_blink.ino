#include <Bridge.h>

char D13value[2];

void setup() {
  pinMode(13,OUTPUT);
  Bridge.begin();
}

void loop() {
  Bridge.get("key",D13value,2);
  int D13int = atoi(D13value);
  digitalWrite(13,D13int);
  delay(50);  
}
