SRC += matrix.c
CUSTOM_MATRIX = lite

#Defined in keyboard.json.
#additional settings in config.h
#PS2_MOUSE_ENABLE = yes
#PS2_ENABLE = yes
#PS2_DRIVER = vendor

#extra quirk - discard first packet
#its' in keymap.c

##ECE1117 support, used in keymap.c
I2C_DRIVER_REQUIRED = yes

#debugging
CONSOLE_ENABLE = yes



