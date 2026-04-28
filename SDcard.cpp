#include <SD.h>
#include "SDcard.h"
#include <SPI.h>
#include "TempSensor.h"

sdDataLogger::sdDataLogger(byte CS, byte MOSI, byte MISO, byte SCK) : isLogging(false), SD_CS(CS), SD_MOSI(MOSI), SD_MISO(MISO), SD_SCK(SCK) {}

sdDataLogger::~sdDataLogger() {
    end();
}

bool sdDataLogger::begin(const char* basefilename) {
    reInitSdSPI();
    if (!SD.begin(SD_CS)) {
        Serial.println("SD card initialization failed!");
        return false;
    }

    // Create a unique filename by appending a number if the file already exists
    String basename(basefilename);
    String filename = "";
    int fileCount = 0;
    bool fileExists;
    do
    {        
      fileCount += 1;
      filename = basename + "_" + String(fileCount) +".csv";
      fileExists = SD.exists(filename.c_str());
    } while(fileExists);

    logFile = SD.open(filename.c_str(), FILE_WRITE);
    if (!logFile) {
        Serial.println("Failed to open log file!");
        return false;
    }
    Serial.println("Logging to: " + filename);
    isLogging = true;
    return true;
}

void sdDataLogger::logData(const char* data) {
    if (isLogging && logFile) {
        logFile.println(data);
        logFile.flush();
    }
}
void sdDataLogger::end() {
    if (isLogging) {
        logFile.close();
        isLogging = false;
    }
}

void sdDataLogger::reInitSdSPI() {
    // SPI reconfiguration - not supported on AVR boards with SD library
    // This function is kept for compatibility
}