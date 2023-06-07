/**
 * Servostation - Library header file
*/  

# pragma once

# include <inttypes.h>
# include <Servo.h>
# include <Arduino.h>

# define SERVO_STATION_AUTHOR "Samuel Noesslboeck"
# define SERVO_STATION_VERSION "0.1.0"

/** Returns the value of a pin in a byte or other integer*/
# define PIN_OF(__val, __pin) ((__val >> __pin) & 0x01)
/** Angle input hysterisis in degrees */
# define ANGLE_INPUT_HYSTERESIS 10

/** All constants and functions for the Servostation */
namespace servostation {
    // Enums
        /** Different types of movement status */
        enum class Status {
            Driving,    // The servos are currently driving
            Ready       // The servos are ready to move
        }; 

        /** Different types of movement directions */
        enum class Direction {
            Left,
            Right
        };  
    // 

    // Constants
        /** Pins of digital inputs */
        const uint8_t DIG_INPUT_PINS[] = {
            2,      // TODO insert correct pin values
            3,
            4,
            5
        };

        /** Pin of analog input pin */
        const uint8_t ANALOG_INPUT_PIN = A5;

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
        const uint8_t DIG_OUTPUT_DIR_INDEX = 1; 

        /** Pins of analog output for the servo motors */
        const uint8_t SERVO_PINS[] = {
            A0, 
            A1,
            A2,
            A3
        };
    // 

    // Status
        /** Main status LED */
        # define STATUS_LED_MAIN LED_BUILTIN
        /** Secondary status led */
        # define STATUS_LED_SEC 12
    // 

    // Statics
        /** Status of the servo station */
        static Status STATION_STATUS;

        /** Array of servos */
        /** The current digital output value written to the pins */
        static uint8_t DIG_OUT_VAL;

        /** The servo controll classes */
        static Servo servos[sizeof(SERVO_PINS) / sizeof(uint8_t)];

        /** Helper variable for blink of status LED */
        static unsigned long LAST_LED_BLINK;

        /** Value of the status led */
        static uint8_t STATUS_LEDS_VAL;
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

    /** Writes the analog signal to the given servo and returns the angle difference */
    int write_servo(uint8_t index, int angle);

    // Status 
    /** Print information about servo station */
    void print_info();

    /** Set the secondary status led */
    void set_sec_status();

    /** Unset the secondary status led */
    void reset_sec_status();

    /** Update function for the status LEDs, call in "loop()"" */
    void update_status_leds();
}