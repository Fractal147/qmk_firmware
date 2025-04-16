# pico_5410

![pico_5410](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [Andrew Witty](https://github.com/Fractal147)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make pico_5410:default

Flashing example for this keyboard:

    make pico_5410:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the (f4/mute key) and plug in the keyboard
* possible this is f4/mute + b, there's more magic available
* **Physical reset button**: Hold on-pcb BOOT button while plugging in 
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (fn-shift-f9)


## Wiring
    Unless stated otherwise, this is the 20 pin 0.5 mm pitch CN1. Right is pin1.
    Touchpad/Trackpoint
        needs 3.3v on pin12
        pi GPIO0 to PS2 data on pin13 of 20pin CN1
        pi GPIO1 to PS2 clk on pin14 of 20pin CN1
        
        Mod: add 0 ohm 0402/0603 links on R17 and R18
        Mod: add 4.7k pullups to 3.3vTP rail from PS2_CLK and PS2_DAT 
            suggest using SMT resistors and test pads nearish R17 and R18
            See photo/drawing of this.
        
    Keyboard
        Needs 3.3v on pin 6
        
        I2C to ECE1117
            I2C_DATA    Pin8 to Pi Pico pin 6 GP4 I2C0SDA
            I2C_CLK     Pin10 to Pi Pico pin 7 GP5 I2C0SCL
            I2C_INT     Pin7 to Not implemented...
        
    Backlight?
        Needs 5v on pin 5...
        Wired to VBUS (5v)

## WORKING:
    Trackpad
    Trackpad L and R click
    Trackpad 2 fingered vertical scroll
    Touchpoint
    Touchpoint L and R click
    Touchpoint scroll button
    Adjust touchpoint scroll sensitivity (set to /20)
    All physical keys
    fn key
    bootloader entry (hold f4 and b when plugging in)
    
## TODO:

    /ideally/ spin touchpoint out to a separate device so the OS could decide sensitivity
        Though this is probably hard.
        
    touchpad horizontal scroll?
        it's triggering in hardware, but I think message is being ignored somehow.
        Note it's not just sending a horizontal scroll message all the time..
            assuming that makey breaky
            
    Pin 0 of keyboard mystery
    
    Backlight.
    
    Caps lock LED
    Mute mic key
    Mute key LED
    
    ECE I2C errors recovery (send reset, re-init)
    
    Touchpad errors detection and recovery - hmm maybe power it from a pico IO pin?
    
    Sleep modes?
    
    Interrupts based on any key press - use ECE sending ALL for instance.
    
    TOUCHPOINT DISABLING.
        e.g. use that mute key
        
    
    
### Keyboard notes
    It's an ECE1117 io controller running the keyboard
    (and it also can tunnel ps/2 data, or SMBUS data from the touchpad, but let's ignore those features)
    MAYBE it's been setup sensibly so that matrix scanning works...by default
    In which case, the matrix changed is simply "has int pin fired?"
    and the reading? Not sure yet.
    
    Since the matrix supports 19 KSO (output) pins, and 8 KSI (input) pins (total 27)
    and the keyboard has ~26 pins unaccounted for (plus 3 blanks - one of which must be a not present LED)
    this suggests that the keyboard matrix is used. Certainly the KSI pins go somewhere.
    
    MUTE_LED, GND, and CAPS_LED are pins 32 to 30
    3 empties, and then 26 matrix.
    Oddly pin 1 goes to GPIO10, and has a 10k pullup.
        Not sure what this means but it's an odd one out.
        Maybe some custom kbd scan is needed.
        Let's ignore it for now.
           
    It's 10khz to 400khz i2c.
        What is QMK??
        
    Keyboard scan - from ECE1117
        It could invert KSO[22:0]. But probably doesn't.
        I should write 0<<6 (KSEN=0) to 0x40 (KSO select)
            as that enables keyboard scan.
            
        Looks like pullups may need to be controlled by a gpio matrix...
        maybe just keyboard scan will just owrk.
        Note that KSO19/GPIO00 may have weirdness.
            Especially bit 6 which is kso/gpio mode for KS019 and GPIO0  - normal... but:
            GPIO00_config bit 7 which has inverted logic
                0 default has pullup en!
                1 = pullup disabled
                but controls all KSI[7:0] pins!
                in GPIO00 0x0A
                
        Note that GPIO01_config at 0x0B should keep bit 7 cleared to 0. I would anyway, but perhaps it's bad?
    
    OK, partially works
    some keys work normally
    some keys trigger every row to be low for that column
    (19 rows for KSO) 8 columns for KSI
    . How? I guess that's a dedicated column for them??
    x\sawq are all multirowers somehow... maybe they float lowish
    
    I think some of the defaults are to not be KSO pins
    I think pin KSI0 is weird and has a separate pullup
    
### I2C
    
