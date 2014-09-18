#include <SoftwareSerial.h>

String tmp="";

const int bleRx = 9, bleTx = 10;  // connect to BLE Module RT0(D0) , TX1(D1)
SoftwareSerial bleSerial(bleRx, bleTx); // RX, TX

void setup()
{ 
  // set the data rate for the SoftwareSerial port
  bleSerial.begin(9600);

  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Serieal Ready");
}

void loop() {

  while (bleSerial.available() > 0)  {
    tmp += char(bleSerial.read());
    delay(2);
  }

  if(tmp.length() > 0) {
    Serial.println(tmp);
    tmp = "";
  }

  if (Serial.available()) {
    bleSerial.write(Serial.read());
  }
}
