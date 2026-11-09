#include <SoftwareSerial.h>
#include "HUSKYLENS.h"

// HuskyLens UART — green (TX from lens) to pin 10, blue (RX into lens) to pin 11
SoftwareSerial huskySerial(10, 11); // RX, TX from Arduino's perspective

HUSKYLENS huskylens;

// Stepper motor pins
#define STEP_PIN 3
#define DIR_PIN  4

// Trigger line — stop belt when Lego Y position is <= this value
// 120 = middle of screen (0-240). Tune this after watching Serial Monitor
int triggerY = 120;

bool stopBelt = false;


void setup() {
  Serial.begin(9600);       // For Serial Monitor debugging
  huskySerial.begin(9600);  // HuskyLens UART

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, HIGH); // Keep your original direction

  // Connect to HuskyLens
  while (!huskylens.begin(huskySerial)) {
    Serial.println("HuskyLens not found — check wiring and make sure Protocol is set to UART on the device!");
    delay(500);
  }

  Serial.println("HuskyLens connected!");

  // Set to Object Tracking mode
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
  Serial.println("Watching for Legos...");
}

void loop() {

for (int i = 0; i<=400; i++){//go

      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(500);

    }
   delay(2000);//2 secs

  // ── Lego detected ────────────────────────────────────────────────────────
  if (huskylens.request() && huskylens.available()) {//scan

    HUSKYLENSResult result = huskylens.read();

    int legoX = result.xCenter;
    int legoY = result.yCenter;

    Serial.print("Lego at X: ");
    Serial.print(legoX);
    Serial.print("  Y: ");
    Serial.println(legoY);

     if (legoY <= triggerY) {

      delay(2000);

      Serial.println(">>> LEGO AT TRIGGER — STOPPING BELT <<<");
    }

  }

   

  }

