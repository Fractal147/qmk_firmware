// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
    )
};


#include <stdbool.h>
#include "ps2_mouse.h"
#include "wait.h"
#include "gpio.h"
#include "host.h"
#include "timer.h"
#include "print.h"
#include "report.h"
#include "debug.h"
#include "ps2.h"


void ps2_mouse_init_user(void) {
    //Quirk: This touchpad combo appears to send garbage data for first few packets
    //Especially if a finger is touching it.
    //Fix: Discard first 100ms of data

    //Note this function does appear to run very often
    //So use hasRun to keep track and only execute once.
    static int hasRun =0;

    //Trash the firt 100ms of data
    if(hasRun ==0){
        hasRun++;
        wait_ms(100); // wait for powering up
        report_mouse_t mouse_report_dummy = {};
        if (pbuf_has_data()) {
            while (pbuf_has_data()) {
                mouse_report_dummy.buttons = ps2_host_recv_response();
                mouse_report_dummy.x       = ps2_host_recv_response();
                mouse_report_dummy.y       = ps2_host_recv_response();
                #    ifdef PS2_MOUSE_ENABLE_SCROLLING
                mouse_report_dummy.v       = -(ps2_host_recv_response() & PS2_MOUSE_SCROLL_MASK);
                #    endif
            }
            mouse_report_dummy.buttons += 1; //just to suppress warnings
        } else {
            if (debug_mouse) print("ps2_mouse: INIT_fail\n");
            /* return here to avoid updating the mouse button state */
            return;
        }
    }
    return;

    // trackpoint sensitivity from reddit:

//     PS2_MOUSE_SEND(0xE2, "trackpoint command");
//
//     PS2_MOUSE_SEND(0x81, "write byte");
//
//     PS2_MOUSE_SEND(0x4A, "sensitivity");
//
//     PS2_MOUSE_SEND(0x60, "data"); // default = x80 (1). range = 0x00 to 0xFF (0 to 1.99)
//
//     PS2_MOUSE_SEND(0xE2, "trackpoint command");
//
//     PS2_MOUSE_SEND(0x81, "write byte");
//
//     PS2_MOUSE_SEND(0x60, "value6");
//
//     PS2_MOUSE_SEND(0x61, "data"); // default = x61
};




void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
    #ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
    #endif
    return true;
}


