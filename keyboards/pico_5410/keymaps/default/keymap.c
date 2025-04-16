// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
	KC_G,	KC_T,	KC_R,	KC_5,	KC_F,	KC_4,	KC_V,	KC_B,
	KC_NUBS,	KC_CAPS,	KC_W,	KC_MUTE,	KC_S,	KC_2,	KC_X,	KC_NO,
	KC_F4,	KC_VOLU,	KC_E,	KC_VOLD,	KC_D,	KC_3,	KC_C,	KC_NO,
	KC_ESC,	KC_TAB,	KC_Q,	KC_GRAVE,	KC_A,	KC_1,	KC_Z,	KC_NO,
	KC_NO,	KC_NO,	KC_PGUP,	KC_NO,	KC_PGDN,	KC_LWIN,	KC_NO,	KC_NO,

	KC_NO,	KC_NO,	KC_NO,	KC_NO,	MO(1),	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_LSFT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_RSFT,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_LCTL,	KC_NO,	KC_NO,	KC_RCTL,	KC_NO,
	KC_LALT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_ALGR,
	KC_UP,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_LEFT,

	KC_NO,	KC_NO,	KC_NO,	KC_INS,	KC_NO,	KC_END,	KC_NO,	KC_RIGHT,
	KC_NO,	KC_NO,	KC_NO,	KC_DEL,	KC_NO,	KC_HOME,	KC_NO,	KC_DOWN,
	KC_F5,	KC_BSPC,	KC_NO,	KC_F9,	KC_NO,	KC_PSCR,	KC_ENT,	KC_SPACE,
	KC_QUOT,	KC_LBRC,	KC_P,	KC_MINUS,	KC_SCLN,	KC_0,	KC_NUHS,	KC_SLSH,
	KC_NO,	KC_BRIU,	KC_O,	KC_F8,	KC_L,	KC_9,	KC_DOT,	KC_NO,

	KC_BRID,	KC_RBRC,	KC_I,	KC_EQUAL,	KC_K,	KC_8,	KC_COMM,	KC_NO,
	KC_H,	KC_Y,	KC_U,	KC_6,	KC_J,	KC_7,	KC_M,	KC_N,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
	)
,
[1] = LAYOUT( //Layer with fn key held
	KC_G,	KC_T,	KC_R,	KC_5,	KC_F,	KC_4,	KC_V,	KC_B,
	KC_NUBS,	KC_CAPS,	KC_W,	KC_F1,	KC_S,	KC_2,	KC_X,	KC_NO,
	KC_F4,	KC_F3,	KC_E,	KC_F2,	KC_D,	KC_3,	KC_C,	KC_NO,
	QK_LLCK,	KC_TAB,	KC_Q,	KC_GRAVE,	KC_A,	KC_1,	KC_Z,	KC_NO,
	KC_NO,	KC_NO,	KC_PGUP,	KC_NO,	KC_PGDN,	KC_LWIN,	KC_NO,	KC_NO,

	KC_NO,	KC_NO,	KC_NO,	KC_NO,	_______,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	MO(2),	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_RSFT,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_LCTL,	KC_NO,	KC_NO,	KC_RCTL,	KC_NO,
	KC_LALT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_ALGR,
	KC_UP,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_LEFT,

	KC_NO,	KC_NO,	KC_NO,	KC_INS,	KC_NO,	KC_F12,	KC_NO,	KC_RIGHT,
	KC_NO,	KC_NO,	KC_NO,	KC_DEL,	KC_NO,	KC_F11,	KC_NO,	KC_DOWN,
	KC_F5,	KC_BSPC,	KC_NO,	KC_F9,	KC_NO,	KC_F10,	KC_ENT,	KC_SPACE,
	KC_QUOT,	KC_LBRC,	KC_P,	KC_MINUS,	KC_SCLN,	KC_0,	KC_NUHS,	KC_SLSH,
	KC_NO,	KC_F7,	KC_O,	KC_F8,	KC_L,	KC_9,	KC_DOT,	KC_NO,

	KC_F6,	KC_RBRC,	KC_I,	KC_EQUAL,	KC_K,	KC_8,	KC_COMM,	KC_NO,
	KC_H,	KC_Y,	KC_U,	KC_6,	KC_J,	KC_7,	KC_M,	KC_N,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
	)
,
[2] = LAYOUT( //Layer with fn key and shift: has special QK boot on f9
	KC_G,	KC_T,	KC_R,	KC_5,	KC_F,	KC_4,	KC_V,	KC_B,
	KC_NUBS,	KC_CAPS,	KC_W,	KC_F1,	KC_S,	KC_2,	KC_X,	KC_NO,
	KC_F4,	KC_F3,	KC_E,	KC_F2,	KC_D,	KC_3,	KC_C,	KC_NO,
	QK_LLCK,	KC_TAB,	KC_Q,	KC_GRAVE,	KC_A,	KC_1,	KC_Z,	KC_NO,
	KC_NO,	KC_NO,	KC_PGUP,	KC_NO,	KC_PGDN,	KC_LWIN,	KC_NO,	KC_NO,

	KC_NO,	KC_NO,	KC_NO,	KC_NO,	_______,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_LSFT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_RSFT,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_LCTL,	KC_NO,	KC_NO,	KC_RCTL,	KC_NO,
	KC_LALT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_ALGR,
	KC_UP,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_LEFT,

	KC_NO,	KC_NO,	KC_NO,	KC_INS,	KC_NO,	KC_F12,	KC_NO,	KC_RIGHT,
	KC_NO,	KC_NO,	KC_NO,	KC_DEL,	KC_NO,	KC_F11,	KC_NO,	KC_DOWN,
	KC_F5,	KC_BSPC,	KC_NO,	QK_BOOT,	KC_NO,	KC_F10,	KC_ENT,	KC_SPACE,
	KC_QUOT,	KC_LBRC,	KC_P,	KC_MINUS,	KC_SCLN,	KC_0,	KC_NUHS,	KC_SLSH,
	KC_NO,	KC_F7,	KC_O,	KC_F8,	KC_L,	KC_9,	KC_DOT,	KC_NO,

	KC_F6,	KC_RBRC,	KC_I,	KC_EQUAL,	KC_K,	KC_8,	KC_COMM,	KC_NO,
	KC_H,	KC_Y,	KC_U,	KC_6,	KC_J,	KC_7,	KC_M,	KC_N,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
)

};

// [0] = LAYOUT( //copy
// 	KC_G,	KC_T,	KC_R,	KC_5,	KC_F,	KC_4,	KC_V,	KC_B,
// 	KC_NUBS,	KC_CAPS,	KC_W,	KC_F1,	KC_S,	KC_2,	KC_X,	KC_NO,
// 	KC_F4,	KC_F3,	KC_E,	KC_F2,	KC_D,	KC_3,	KC_C,	KC_NO,
// 	KC_ESC,	KC_TAB,	KC_Q,	KC_GRAVE,	KC_A,	KC_1,	KC_Z,	KC_NO,
// 	KC_NO,	KC_NO,	KC_PGUP,	KC_NO,	KC_PGDN,	KC_LWIN,	KC_NO,	KC_NO,
//
// 	KC_NO,	KC_NO,	KC_NO,	KC_NO,	MO(1),	KC_NO,	KC_NO,	KC_NO,
// 	KC_NO,	KC_LSFT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_RSFT,	KC_NO,
// 	KC_NO,	KC_NO,	KC_NO,	KC_LCTL,	KC_NO,	KC_NO,	KC_RCTL,	KC_NO,
// 	KC_LALT,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_ALGR,
// 	KC_UP,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_LEFT,
//
// 	KC_NO,	KC_NO,	KC_NO,	KC_INS,	KC_NO,	KC_F12,	KC_NO,	KC_RIGHT,
// 	KC_NO,	KC_NO,	KC_NO,	KC_DEL,	KC_NO,	KC_F11,	KC_NO,	KC_DOWN,
// 	KC_F5,	KC_BSPC,	KC_NO,	KC_F9,	KC_NO,	KC_F10,	KC_RETN,	KC_SPACE,
// 	KC_QUOT,	KC_LBRC,	KC_P,	KC_MINUS,	KC_SCLN,	KC_0,	KC_NUHS,	KC_SLSH,
// 	KC_NO,	KC_F7,	KC_O,	KC_F8,	KC_L,	KC_9,	KC_DOT,	KC_NO,
//
// 	KC_F6,	KC_RBRC,	KC_I,	KC_NO,	KC_K,	KC_8,	KC_COMM,	KC_NO,
// 	KC_H,	KC_Y,	KC_U,	KC_6,	KC_J,	KC_7,	KC_M,	KC_N,
// 	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
// 	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
// 	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
// )




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


