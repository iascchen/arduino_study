#!/usr/bin/python

'''

reference docs is : http://forum.arduino.cc/index.php?topic=188998.0

This file is used with sketch : python_blink.ino

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

'''

import sys
sys.path.insert(0, '/usr/lib/python2.7/bridge/')

from bridgeclient import BridgeClient as bridgeclient

if __name__ == '__main__':
    try:
        raw = sys.argv[1]
    except IndexError as e1:
        raw = raw_input('>>> Input (0 or 1) : ')

    _client = bridgeclient()
    _client.put('key', raw)
    print _client.get('key')