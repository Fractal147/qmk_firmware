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
#define ECE_TIMEOUT 50 // ms for timeout
//Pico is probably chibios.
//GPIO0/1 used for ALPS touchpad


void matrix_init_custom(void) {
    // TODO: initialize hardware here
    //NOTE print commands DO NOT WORK here.



    //The first access to the ECE1117 must be a write to the Upstream Bus Control Register to
    //configure the Interface Selection field to the desired interface type (10b or 11b). This is
    //required so that Oscillator control works properly and so that the bus type does not
    //inadvertently switch during use.
    //Write to 0xFA
        //11b SMBus interface enabled

    //Send a soft reset (to 0xF5) send 0x01
    //probably redo xFA again, it won't hurt.

    //when SMbus slave ARA functionality not required, clear ARA bit to 0.
        //note this does something with interrupts? Note 6-2
        //it disables the ECE1117 sending interrupts on SMB_INT_UP pin. Doh.
        //ah then master does Alert Response Address Read Byte command,... then the ECE1117 wins arbitration? and then clears it's ARA bit., and the pin is deasserted. You have to write to ARA again. Huh. Polling for now.

    //Read device ID (should be 0x43_) from 0xFC


    //After a powerup sequence, two writes to the POR Control Register on page 24 are
    //required to set and then clear the POR bit.


    //enable keyboard scan- write 0x00 to 0x40
    //uint8_t counter =0;
    for(uint8_t counter =0; counter <8 ;counter++){
        printf("kbd_matrix_init: counter %u\n", counter);
        wait_ms(100); // wait for powering up seems to be about 700 ms typically total
    }

    i2c_init();
    uint8_t buf[] = {0};


    buf[0] = 0x03; //SMBus yes, ARA no.
    i2c_status_t err = I2C_STATUS_SUCCESS;
    err |= i2c_write_register(ECE_ADDR, 0xFA, buf,sizeof(buf), ECE_TIMEOUT);
    printf("i2c: setup xFA set to 0x03: err = %i \n", (int8_t) err);


    //Setup GPIO10 as open drain outputs with pullup
    // buf[0] = 0b00110001;
    // err |= i2c_write_register(ECE_ADDR, 0x12, buf,sizeof(buf), ECE_TIMEOUT);
    // //and write 1 to set it up as high /pulled up by external
    // buf[0] = 0x01;
    // err |= i2c_write_register(ECE_ADDR, 0x06, buf,sizeof(buf), ECE_TIMEOUT);


    //Setup GPIO00
    //Output open drain with pullup, mux=1
    buf[0] = 0b01110001;
    err |= i2c_write_register(ECE_ADDR, 0x0A, buf,sizeof(buf), ECE_TIMEOUT);

    //setup GPUI01
    //Output open drain with pullup, mux =1
    buf[0] = 0b01110001;
    err |= i2c_write_register(ECE_ADDR, 0x0B, buf,sizeof(buf), ECE_TIMEOUT);
    //and write 1 to both to set it up as high /pulled up by external
    buf[0] = 0x03;
    err |= i2c_write_register(ECE_ADDR, 0x05, buf,sizeof(buf), ECE_TIMEOUT);


    //Setup GPIO23
    //Output open drain with pullup, mux=1
    buf[0] = 0b01110001;
    err |= i2c_write_register(ECE_ADDR, 0x1D, buf,sizeof(buf), ECE_TIMEOUT);
    //and write 1 to set it up as high /pulled up by external
    buf[0] = 0x01;
    err |= i2c_write_register(ECE_ADDR, 0x07, buf,sizeof(buf), ECE_TIMEOUT);

    //(could setup GPIO21/22 but they are disconnected)




    print("kbd_matrix_init: pre flash\n");
    gpio_set_pin_output(GP25);
    gpio_write_pin_high(GP25);
    wait_ms(100); // wait for powering up -
    print("kbd_matrix_init: post flash\n");
    gpio_set_pin_input(GP25);

    if(err != I2C_STATUS_SUCCESS){
        gpio_set_pin_output(GP25);
        gpio_write_pin_high(GP25);
        wait_ms(100); // wait for powering up
        gpio_write_pin_low(GP25);
        wait_ms(100); // wait for powering up
        gpio_write_pin_high(GP25);
        wait_ms(100); // wait for powering up
        gpio_write_pin_low(GP25);
        wait_ms(100); // wait for powering up
        gpio_write_pin_high(GP25);
        wait_ms(100); // wait for powering up
        gpio_write_pin_low(GP25);
        wait_ms(100); // wait for powering up
        printf("total I2C error = %i \n", (int8_t) err);
        gpio_set_pin_input(GP25);
    }


    //OK should configure KSO pins as open drain outputs. any shared GPIO should be pulled up.
    //No predriving
    //Note the KSI inputs all 8.. are default pulledup
    //so a low on the matrix is a HIT
    //and therefore... also if nothing is active and there's a low it's a mystery pin.
    //so it could be a 19 outputs controlled, +1, and 8 inputs.
    //for sleep if it drives all KSI lines low then I can wake on int.


    return;

}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here
    static uint8_t runCount=0;
    i2c_status_t err = I2C_STATUS_SUCCESS;
    uint8_t buf[] = {0};

    if (runCount==0) {
        runCount++;

        //read VERSION register
        err = i2c_read_register(ECE_ADDR, 0xFC, buf,sizeof(buf), ECE_TIMEOUT);


        printf("i2c: version %02x, err= %i \n", buf[0],err);
    }




    //Keyboard scanning then:
    //It could...leave the ECE117 with all KSOs assered low
    //Then check the KSI status to see if it's recieved a toggle.
    //or it could just scan all KSOs 1 by 1.
    //A matrix row is just an integer, so feed it bits.
    //1 means pressed, 0 means unpressed.

    matrix_row_t new_matrix[MATRIX_ROWS]={0};

    //note implicit pin 1 has some pressed keys unless it's written off...
    uint8_t row =0; //this linearly ticks up.
    for(uint8_t kso=0x00; kso<=0x16; kso++)
    {
        if(kso ==0x07) { kso =0x0b;} //there's a gap in the address table

        buf[0] = (0<<6) | kso; //KSEN=0(active), drive select KSO low.
        err |= i2c_write_register(ECE_ADDR, 0x40, buf,sizeof(buf), ECE_TIMEOUT);

        wait_us(50); //maybe not needed

        //read KSI input register
        err |= i2c_read_register(ECE_ADDR, 0x41, buf,sizeof(buf), ECE_TIMEOUT);

        if (err == I2C_STATUS_SUCCESS){
            new_matrix[row] = ~buf[0]; //since pin goes low (0) when pressed
            //Read GPIO10 ....
            // err |= i2c_read_register(ECE_ADDR, 0x01, buf,sizeof(buf), ECE_TIMEOUT);
            // new_matrix[row] |= (((~buf[0])&0x01)<<8);

        } else {
            //i2c error, skip silently
            new_matrix[row] = current_matrix[row];
        }
        row++;
    }

    //Disable all KSOs:
    buf[0] = (1<<6); //KSEN=1(disabled all KSO)
    i2c_write_register(ECE_ADDR, 0x40, buf,sizeof(buf), ECE_TIMEOUT);

    //For GPIO10/Row20 - set it to low
/*
    err |= i2c_read_register(ECE_ADDR, 0x06, buf,sizeof(buf), ECE_TIMEOUT);
    buf[0] = buf[0] & (~0x01); //set first bit to 0
    err |= i2c_write_register(ECE_ADDR, 0x06, buf,sizeof(buf), ECE_TIMEOUT);

    wait_us(50); //maybe not needed

    //read KSI input register
    err |= i2c_read_register(ECE_ADDR, 0x41, buf,sizeof(buf), ECE_TIMEOUT);

    if (err == I2C_STATUS_SUCCESS){
        new_matrix[row] = ~buf[0]; //since pin goes low (0) when pressed
    } else {
        //i2c error, skip silently
        new_matrix[row] = current_matrix[row];
    }
    //set first bit to 1 again. (open drain, inactive)
    buf[0] = buf[0] | (0x01); //set first bit to 0
    err |= i2c_write_register(ECE_ADDR, 0x06, buf,sizeof(buf), ECE_TIMEOUT);*/


    //here's where gpio 10 would be.

    //TODO: handle GPIO10 as row 20.




    matrix_has_changed = memcmp(current_matrix, new_matrix, sizeof(new_matrix));

    if (matrix_has_changed) {
        memcpy(current_matrix, new_matrix, sizeof(new_matrix));
    }
    return matrix_has_changed;

}
