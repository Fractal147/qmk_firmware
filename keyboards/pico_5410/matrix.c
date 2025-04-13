#include <stdint.h>
#include <stdbool.h>
#include "matrix.h"
#include "wait.h"
#include "action_layer.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "gpio.h"
// Not here #include "expander.h"


//////////////////KEYBOARD//////////
//Probably should make an ECE1117 file or something but...
#include "i2c_master.h"

#define ECE_ADDR (0b0111000 << 1) //0111 000 as SMB_ADDR is pulled low.
//Pico is probably chibios.
//GPIO0/1 used for ALPS touchpad


void matrix_init_custom(void) {
    // TODO: initialize hardware here
    //NOTE print commands DO NOT WORK here.

    print("kbd_matrix_init\n");
    gpio_set_pin_output(GP25);
    gpio_write_pin_high(GP25);
    wait_ms(100); // wait for powering up
    print("kbd_matrix_slp\n");
    gpio_set_pin_input(GP25);

    return;

}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here


    return matrix_has_changed;
}
