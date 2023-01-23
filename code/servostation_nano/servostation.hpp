/**
 * Servostation - Library header file
*/  

# pragma once

# include <inttypes.h>
# include <Servo.h>
# include <Arduino.h>

/** All constants and functions for the Servostation */
namespace servostation
{
    // Constants
        /** Pins of digital inputs */
        const uint8_t DIG_INPUT_PINS[] = {
            2,      // TODO insert correct pin values
            3,
            4,
            5
        };

        /** Pin of analog input pin */
        const uint8_t ANALOG_INPUT_PIN = A7;

        /** Pins of digital outputs */
        const uint8_t DIG_OUTPUT_PINS[] = {
            6,
            7,
            8,
            9
        };

        /** Index of the status output pin in the DIG_OUTPUT_PINS constant */
        const uint8_t DIG_OUTPUT_STATUS_INDEX = 0; 
        /** Index of the direction output pin in the DIG_OUTPUT_PINS constant */
        const uint8_t DIG_OUTPUT_DIR_INDEX = 0; 

        /** Pins of analog output for the servo motors */
        const uint8_t SERVO_PINS[] = {
            A0, 
            A1,
            A2,
            A3
        };
    // 

    // Statics
        /** The current digital output value written to the pins */
        static uint8_t dig_out_val = 0;

        /** The servo controll classes */
        static Servo servos[sizeof(SERVO_PINS) / sizeof(uint8_t)];
    //

    // Enums
        /** Different types of movement status */
        enum Status {
            Driving, 
            Ready
        }; 

        /** Different types of movement directions */
        enum Direction {
            Left,
            Right
        }; 
    // 

    /** Setup the servostation by setting all pinmodes etc.  
     *  Returns an error (result != 0) if one occures
     */
    uint8_t setup();

    /** Reads the total byte value of the digital input signal sent */
    uint8_t read_dig();

    /** Get the current digital output being written */
    uint8_t get_dig_output();


    /** Write the given value val to the digital outputs of the station */
    void write_dig(uint8_t val);

    /** Write the current movement status to the digital output of the station */
    void write_status(Status status);

    /** Write the current movement direction to the digital output of the station */
    void write_dir(Direction dir);

    /** Read the analog value being written to the arduino nano and convert it into an angle */
    int read_analog_ang();

    /** Writes the analog signal to the given servo 
     * \returns The angle difference
    */
    int write_servo(uint8_t index, int angle);
}