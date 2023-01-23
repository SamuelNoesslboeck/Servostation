# include "servostation.hpp"

# define UPDATE_BIT 2

void setup() {
    if (servostation::setup()) {
        // Error
    }
}

void loop() {
    uint8_t input = servostation::read_dig();

    // Update by hardware triggered
    if ((input & (0x1 << UPDATE_BIT)) >> UPDATE_BIT) {
        uint8_t index = input & (~(0xFF << UPDATE_BIT));

        int delta_angle = servostation::write_servo(
            index, 
            servostation::read_analog_ang()
        );

        if (delta_angle > 0) {
            servostation::write_dir(servostation::Left);
        } else if (delta_angle < 0) {
            servostation::write_dir(servostation::Right);
        }
    }
}