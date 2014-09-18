/**
 * Auther : iascchen@gmail.com
 * Date : 2014-09-18
 * Link : https://github.com/iascchen/arduino_study/src/bt_uart
 * 
 * Use SoftwareSerial to access microduino BT module in batch mode.
 * 
 * Send command from serieal:
 * d : Diagnostic
 * s : Set iBeacon mode
 * r : Renew
 * h : Help
 * 
 * You also can Send other BLE command such as : AT or AT+XXX
 * 
 **/
#include <SoftwareSerial.h>

// General
byte cmdByte;
const int interval = 1000;

// Diagnostic
char* diag_cmds[] = {
  "AT" , 
  "AT+VERS?",
  "AT+NAME?", 
  "AT+ADDR?", 
  "AT+UUID?", 
  "AT+CHAR?", 

  "AT+MODE?",
  "AT+RSSI?",
  "AT+NOTI?", 

  "AT+BAUD?", 
  "AT+PARI?",
  "AT+STOP?", 
  "AT+BIT7?", 

  "AT+ADVI?", 
  "AT+BATT?",
  "AT+PIO1?",

  //"AT+ROLE?",

  "AT+IBEA?",
  "AT+IBE0?", 
  "AT+IBE1?",
  "AT+IBE2?",
  "AT+IBE3?",
  "AT+MARJ?", 
  "AT+MINO?",
  "AT+MEA??",
  "AT+PWRM?",
  "AT+POWE?"};

char* ibeacon_cmds[] = {
  "AT+RENEW" , 
  "AT+RESET" ,

  "AT", 
  "AT+MARJ0x0001",
  "AT+MINO0x0002", 
  "AT+ADVI5", 
  "AT+NAMEDOPEY", 
  "AT+ADTY3",
  "AT+IBEA1",
  "AT+DELO2",
  "AT+PWRM0", 

  "AT+RESET"};

char* renew_cmds[] = {
  "AT+RENEW",
  "AT+RESET",
  "AT"}; 

char **cmdSet;
char *blecmd;
String tmp="";

int i, len;

const int bleRx = 9, bleTx = 10;  // connect to BLE Module RT0(D0) , TX1(D1)
SoftwareSerial bleSerial(bleRx, bleTx); // RX, TX

void showBleSerialReturn(){
  while (bleSerial.available() > 0)  {
    tmp += char(bleSerial.read());
    delay(2);
  }

  if(tmp.length() > 0) {
    Serial.print("\t");
    Serial.println(tmp);
  }
  else{
    if (i < len){
      Serial.println();
    }
  }
}

void sendBleCmds(){
  if (i < len){
    blecmd = cmdSet[i++];
    Serial.print(blecmd);
    bleSerial.write(blecmd);

    delay(interval);
  }
}

void processCommand(){
  if (Serial.available() > 0) {
    cmdByte = Serial.read();

    switch (cmdByte) {
    case 'd' :
      Serial.println("\n==> Diagnostic...");
      cmdSet = diag_cmds;
      len = sizeof(diag_cmds) / sizeof(char*);
      i = 0;
      break;

    case 's' :
      Serial.println("\n==> Set iBeacon...");
      cmdSet = ibeacon_cmds;
      len = sizeof(ibeacon_cmds) / sizeof(char*);
      i = 0;
      break;

    case 'r' :
      Serial.println("\n==> Renew...");
      cmdSet = renew_cmds;
      len = sizeof(renew_cmds) / sizeof(char*);
      i = 0;
      break;

    case 'h' :
      Serial.println("\n==> Help...");
      Serial.println("\nh : Help \nd : Diagnostic \ns : Set iBeacon \nr : Renew \nAT... : Other BLE Command");
      break;

    default:
      bleSerial.write(cmdByte);
      Serial.print(char(cmdByte));
    }
  }
}

void setup()
{ 
  // set the data rate for the SoftwareSerial port
  bleSerial.begin(9600);

  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("\nSerieal Ready");
}

void loop() {
  showBleSerialReturn();
  tmp = "";

  sendBleCmds();

  processCommand();
}

