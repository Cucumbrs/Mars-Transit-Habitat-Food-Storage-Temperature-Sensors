#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "TempSensor.h"
#include "SDcard.h"

sdDataLogger logger;  // Global logger instance
bool idleScanning2 = false;

bool ReadSDCard() {
  Serial.println("\nSD Card Contents:");
  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) {
      // no more files
      break;
    }
    Serial.print(entry.name());
    Serial.print(": ");
    while (entry.available()) {
      Serial.write(entry.read());
    }
    Serial.println();
    entry.close();
  }
  return true;
}

void TemperatureScanningMode() {
  Serial.println("\nInitializing SD card for logging...");
  if (!logger.begin("temperature_log")) {
    Serial.println("Warning: SD card initialization failed! Logging to Serial only.");
  } else {
    Serial.println("SD card ready. Entering Temperature logging mode.");
  }
  
  delay(1000);
  Serial.println("Press any key to return to menu.");
  idleScanning2 = true;
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Fridge Temperature Sensor with SD Card Logging");
  Serial.println("Press '1' to read SD card contents.");
  Serial.println("Press '2' to enter Temperature logging mode.");

  logger = sdDataLogger(); // Initialize the logger instance
}

unsigned long lastTime = 0;

void loop() {
  if (idleScanning2) {
    if (millis() > lastTime + 20000) {
      loopTempSensor();
      lastTime = millis();
    }
    if (Serial.available() > 0) {
      Serial.read(); // Clear the input
      idleScanning2 = false;
      Serial.println("\nExiting Temperature logging mode. Returning to menu.");
      Serial.println("Press '1' to read SD card contents.");
      Serial.println("Press '2' to enter Temperature logging mode.");
    }
    return;
  }

  if (Serial.available() > 0) {
    char choice = Serial.read();
    if (choice == '1') {
      ReadSDCard();
    } else if (choice == '2') {
      TemperatureScanningMode();
    } else {
      Serial.println("Invalid choice. Press '1' or '2'.");
    }
  }
}