#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class sdDataLogger {
public:
    sdDataLogger(byte CS = 10, byte MOSI = 11, byte MISO = 12, byte SCK = 13);
    ~sdDataLogger();
    bool begin(const char* filename);
    void logData(const char* data);
    void end();
    bool isInitialized() { return isLogging; }
private:
    void reInitSdSPI();
    File logFile;
    bool isLogging;
    byte SD_CS = 10; // Chip select pin for SD card
    byte SD_MOSI = 11;
    byte SD_MISO = 12;
    byte SD_SCK = 13;
};