//#define PS2_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the PS2 implementation uses the PIO0 peripheral

//Seems to be a pair of fingers is scrolling, at least vertical.
#define PS2_MOUSE_ENABLE_SCROLLING

//So that moving a pair of fingers down moves page down, invert it.
//#define PS2_MOUSE_INVERT_V
#define PS2_MOUSE_INVERT_V_DIRECT

//This seems to be fine, note the first 100ms of messages are purged later in keymap.c
#define PS2_MOUSE_INIT_DELAY 500

//for the touchpoint scroll only, it seems.
#define PS2_MOUSE_SCROLL_DIVISOR_V 20
#define PS2_MOUSE_SCROLL_DIVISOR_H 20


//for the keyboard bit
#define I2C_DRIVER  I2CD0
#define I2C1_SDA_PIN    GP4
#define I2C1_SCL_PIN    GP5

#define MATRIX_ROWS 20
#define MATRIX_COLS 8
