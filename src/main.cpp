#include <Arduino.h>
#include <WiFiNINA.h>

#include "schrotti.h"

Schrotti* schrotti = nullptr;

void setup() {
  WiFi.end();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Turn off the built-in LED
  schrotti = new Schrotti(90,90,90,90);
  delay(5000);
}

void loop() {
  // fl, fr, bl, br
  schrotti->walk_blocking(0,90,90,0);
  delay(100);
  schrotti->walk_blocking(90,180,180,90);
  delay(100);
  schrotti->walk_blocking(90,0,0,90);
  delay(100);
  schrotti->walk_blocking(180,90,90,180);
  delay(100);
}