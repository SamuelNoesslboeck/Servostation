# Servostation

## Setting a servo angle

### Digital input byte

An input byte will be read by the arduino on pins 2-5

- 2-3 (bit 0-1): index of servo to modify (2 bits means index from 0 - 3)
- 4 (bit 2): update pin, if set to high, the values of the servo will be updated
- 5 (bit 3): reserved

### Analog angle input



## Response

### Serial messages

### Status LEDS

The station has two status leds, a `main` and a `secondary` one. If the main one:

- blinks fast (about 5 times per second) then the station is ready and waiting for input
