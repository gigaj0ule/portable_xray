// Sounds ----------------------------

#define SOUND_MENU_AFFIRM      0
#define SOUND_MENU_NOT_AFFIRM  1 
#define SOUND_CHARGER_INSERTED 2
#define SOUND_CHARGER_REMOVED  3
#define SOUND_WAKEUP           4
#define SOUND_XRAY             5
#define SOUND_CANCEL_XRAY      6
#define SOUND_BATTERY_DEAD     7


// Animations -----------------------

#define ANIM_CHARGER_INSERTED  0
#define ANIM_CHARGER_REMOVED   1
#define ANIM_CHARGER_REMOVED   2 
#define ANIM_APERTURE          3
#define ANIM_BATTERY_DEAD      4


// PINS -----------------------------

#define PIN_BTRX      0
#define PIN_BTTX      1
#define PIN_LCD_CS1   2
#define PIN_LCD_CS2   3
#define PIN_BUZZER    4
#define PIN_BACKLIGHT 5
#define PIN_LCD_D7    6
#define PIN_BUTTON_2  7
#define PIN_BUTTON_1  8
#define PIN_BUTTON_0  9
#define PIN_LCD_EN    10
#define PIN_LCD_RW    11
#define PIN_LCD_DI    12
#define PIN_LCD_D6    13
#define PIN_LCD_D5    14
#define PIN_LCD_D4    15
#define PIN_LCD_D3    16
#define PIN_LCD_D2    17
#define PIN_I2C_SDA   18
#define PIN_I2C_SCL   19
#define PIN_LCD_D0    20
#define PIN_LCD_D1    21
#define PIN_WATCHDOG  22
#define PIN_VSENSE    23


// EXPANDED PINS -----------------------

//#define EXP_PIN_                  0
#define EXP_PIN_BATTERY_MON_ENABLE    1
//#define EXP_PIN_                    2
//#define EXP_PIN_                    3
//#define EXP_PIN_                    4
#define EXP_PIN_BT_ENABLE           5
#define EXP_PIN_CATHODE_ENABLE      6
#define EXP_PIN_BIG_BOOST_ENABLE    7
#define EXP_PIN_BRIDGE_DISABLE      8
//#define EXP_PIN_                    9
//#define EXP_PIN_                    10
//#define EXP_PIN_                    11
//#define EXP_PIN_                    12
#define EXP_PIN_BATT_CHARGE_DISABLE 13
#define EXP_PIN_BATT_CURRENT_MODE   14
#define EXP_PIN_CHARGE_SENSOR       15


// I2C BUS ----------------------------

#define I2C_EXPANDER_ADDRESS    0x20
#define BATTERY_MONITOR_ADDRESS 0x08
#define DIGITAL_POT_ADDRESS     0

#define HEATER 1
#define BOOST  0


// SYSTEM MENU STUFF ----------------------

#define MMS_ENERGY    0
#define MMS_EXPOSURE  1
#define MMS_TIMER     2
#define MMS_XRAY      3
#define MMS_SYSTEM    4

#define SSS_SHUTDOWN   0
#define SSS_BATTERY    1
#define SSS_BLUETOOTH  2  /* Bluetooth (not) Scrapped & (still) Useless */

#define MMS_LIST_SIZE 4
#define SSS_LIST_SIZE 2


// CONFIGURATIONS -------------------------

#define MIN_KVP   40
#define MAX_KVP   70

#define MIN_MAS   200
#define MAX_MAS   6000

#define MIN_TIM   3
#define MAX_TIM   30

#define MIN_CATHODE_VAL 175
#define MAX_CATHODE_VAL 204

#define TIMER_BACKLIGHT_RESET   10
#define TIMER_SHUTDOWN_RESET    120

#define BACKLIGHT_BRIGHT        64
#define BACKLIGHT_DIM           12



// PITCHES --------------------------------

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// VARIABLE_INDEXES ---------------

#define MIN 0
#define MAX 1
#define MEAN 2
