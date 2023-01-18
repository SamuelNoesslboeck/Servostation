# include "servostation.hpp"

void setup() {
    if (servostation::setup()) {
        // Error
    }
}

void loop() {
    uint8_t input = servostation::read_dig();

    
}