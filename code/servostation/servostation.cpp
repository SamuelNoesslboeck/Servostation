# include "servostation.hpp"

# include <Arduino.h>

namespace servostation {
    uint8_t setup() {
        // Serials
        Serial.begin(115200);

        // Setup the analog input pin to read the angle from
        pinMode(ANALOG_INPUT_PIN, INPUT);

        // Setup status leds
        pinMode(STATUS_LED_MAIN, OUTPUT);
        pinMode(STATUS_LED_SEC, OUTPUT);

        // Setup all digitalinput pins
        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            pinMode(DIG_INPUT_PINS[i], INPUT);
        }

        // Setup all digital output pins
        for (uint8_t i = 0; i < (sizeof(DIG_OUTPUT_PINS) / sizeof(uint8_t)); i++) {
            pinMode(DIG_OUTPUT_PINS[i], OUTPUT);
        }

        // Setup all analog output pins for the servos
        for (uint8_t i = 0; i < (sizeof(SERVO_PINS) / sizeof(uint8_t)); i++) {
            if (!servos[i].attached()) {
                servos[i].attach(SERVO_PINS[i]);
            }
        }

        // Set statics
        STATION_STATUS = Status::Ready;
        DIG_OUT_VAL = 0;
        LAST_LED_BLINK = millis();
        STATUS_LEDS_VAL = 0;

        return 0;   // Done without erros
    }

    // Read
    uint8_t read_dig() {
        uint8_t sum = 0; 

        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            sum |= digitalRead(DIG_INPUT_PINS[i]) << i;
        }

        return sum;
    }

    uint8_t get_dig_output() {
        return DIG_OUT_VAL;
    }

    // Write
    void write_dig(uint8_t val) {
        for (uint8_t i = 0; i < (sizeof(DIG_INPUT_PINS) / sizeof(uint8_t)); i++) {
            digitalWrite(DIG_OUTPUT_PINS[i], (val >> i) & 0x01);
        }
        
        DIG_OUT_VAL = val;      // Update the static variable
    }

    void write_status(Status status) {
        digitalWrite(DIG_OUTPUT_PINS[DIG_OUTPUT_STATUS_INDEX], (uint8_t)status);
        
        DIG_OUT_VAL &= ~(0x01 << DIG_OUTPUT_STATUS_INDEX);
        DIG_OUT_VAL |= ((uint8_t)status << DIG_OUTPUT_STATUS_INDEX);
    }

    void write_dir(Direction dir) {
        digitalWrite(DIG_OUTPUT_PINS[DIG_OUTPUT_DIR_INDEX], (uint8_t)dir);

        DIG_OUT_VAL &= ~(0x01 << DIG_OUTPUT_DIR_INDEX);
        DIG_OUT_VAL |= ((uint8_t)dir << DIG_OUTPUT_DIR_INDEX);
    }

    
    int read_analog_ang() {
        int input = analogRead(ANALOG_INPUT_PIN); 
        return map(input, 0, 1023, 0, 180); 
    }

    int write_servo(uint8_t index, int angle) {
        int delta_angle = angle - servos[index].read();
        if (abs(delta_angle) > ANGLE_INPUT_HYSTERESIS) {
            servos[index].write(angle);
            
            char msg [48];
            sprintf(msg, " -> Writing new value %d to servo %d\n", angle, index);
            Serial.print(msg);
        }
        return delta_angle;
    }

    // Status
    void print_info() {
        Serial.write("- Author: ");
        Serial.write(SERVO_STATION_AUTHOR);
        Serial.write("\n- Version: ");
        Serial.write(SERVO_STATION_VERSION);
        Serial.write("\n\n"); 
    }

    void set_sec_status() {
        STATUS_LEDS_VAL |= 0x02;
        digitalWrite(STATUS_LED_SEC, HIGH);
    }

    void reset_sec_status() {
        STATUS_LEDS_VAL &= ~0x02;
        digitalWrite(STATUS_LED_SEC, LOW);
    }

    void update_status_leds() {
        // LED blinks fast when the station is ready
        if (STATION_STATUS == Status::Ready) {
            if ((millis() - LAST_LED_BLINK) > 100) {
                STATUS_LEDS_VAL ^= 0x01;                                       // Switch status led
                digitalWrite(STATUS_LED_MAIN, PIN_OF(STATUS_LEDS_VAL, 0));     // Write values of status led
                LAST_LED_BLINK = millis();
            }

        // LED lights continously when the station is driving
        } else if (STATION_STATUS == Status::Driving) {
            if (PIN_OF(STATUS_LEDS_VAL, 0) == LOW) {
                STATUS_LEDS_VAL |= 0x01;                                         // Enable main status led
            }
        }
    }
}