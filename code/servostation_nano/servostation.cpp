# include "servostation.hpp"

# include <Arduino.h>

namespace servostation 
{
    uint8_t setup() {
        // Inputs
        pinMode(ANALOG_INPUT_PIN, INPUT);

        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            pinMode(DIG_INPUT_PINS[i], INPUT);
        }

        // Outputs
        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            pinMode(DIG_OUTPUT_PINS[i], OUTPUT);
        }

        return 0;   // Done without erros
    }

    uint8_t read_dig() {
        uint8_t sum = 0; 

        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            sum += digitalRead(DIG_INPUT_PINS[i]) << i;
        }

        return sum;
    }

    uint8_t get_dig_output() {
        return dig_out_val;
    }

    void write_dig(uint8_t val) {
        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            digitalWrite(DIG_OUTPUT_PINS[i], (val >> i) & 0x01);
        }
        
        dig_out_val = val;      // Update the static variable
    }

    void write_status(Status status) {
        digitalWrite(DIG_OUTPUT_PINS[DIG_OUTPUT_STATUS_INDEX], (uint8_t)status);
        
        dig_out_val &= ~(0x01 << DIG_OUTPUT_STATUS_INDEX);
        dig_out_val |= ((uint8_t)status << DIG_OUTPUT_STATUS_INDEX);
    }

    void write_dir(Direction dir) {
        digitalWrite(DIG_OUTPUT_PINS[DIG_OUTPUT_DIR_INDEX], (uint8_t)dir);

        dig_out_val &= ~(0x01 << DIG_OUTPUT_DIR_INDEX);
        dig_out_val |= ((uint8_t)dir << DIG_OUTPUT_DIR_INDEX);
    }
}