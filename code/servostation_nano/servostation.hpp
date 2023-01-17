/**
 * Servostation - Library header file
*/  


# pragma once

# include <inttypes.h>

/** All constants and functions for the servostation */
namespace servostation
{
    // Constants
        /** Pins of digital inputs */
        const uint8_t DIG_INPUT_PINS[] = {
            0,      // TODO insert correct pin values
            1,
            2,
            3
        };

        /** Pin of analog input pin */
        const uint8_t ANALOG_INPUT_PIN = 0;

        /** Pin of digital outputs */
        const uint8_t DIG_OUTPUT_PINS[] = {
            0,
            1
        };

        /** Index of the status output pin in the DIG_OUTPUT_PINS constant */
        const uint8_t DIG_OUTPUT_STATUS_INDEX = 0; 
        /** Index of the direction output pin in the DIG_OUTPUT_PINS constant */
        const uint8_t DIG_OUTPUT_DIR_INDEX = 0; 

        const uint8_t SERVO_PINS[] = {
            0, 
            1,
            2,
            3
        };
    // 

    // Statics
        /** The current digital output value written to the pins */
        static uint8_t dig_out_val = 0;
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


    /** Converts the analog input signal into an angle */
    float input_to_angle(int analog);

    /** Converts the angle into an analog output signal */
    int angle_to_output(float angle);

    /** Writes the analog signal to the given servo */
    void write_servo(uint8_t index, int analog);
}