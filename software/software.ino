// INCLUDED FILES ------------------------------------------
#include <openGLCD.h>
#include <Wire.h>
#include <EEPROM.h>
#include <bitmaps/allBitmaps.h>
#include "constants.h"
#include "lang_english.h"


// Dev mode? ---------------------------------------------
#define NO_X_RAY false


// STATE VARIABLES ---------------------------------------

char STATE_main_menu_selection    = 0;
char STATE_sys_menu_selection     = 0;
char STATE_ui_button              = 0;
char STATE_bluetooth_enabled      = 1;
char STATE_auto_poweroff_enabled  = 1;
char STATE_KVP                    = MIN_KVP;
int  STATE_MAS                    = MIN_MAS;
char STATE_TIM                    = MIN_TIM;


// BINARY FLAG VARIABLES ----------------------------------

boolean FLAG_watchdog              = 0;
boolean FLAG_poweroff              = 0;
boolean FLAG_auto_shutdown         = 0;
boolean FLAG_pack_dead             = 0;
boolean FLAG_initiate_countdown    = 0;
boolean FLAG_initiate_exposure     = 0;
boolean FLAG_charger_inserted      = 0;
boolean FLAG_onesecond             = 0;
boolean FLAG_disable_poweroff      = 0;


// MAPS and ARRAYS ------------------------------------------

char buttonMap[8]                 = {0,'l','e','b','a','u','d','r'};

float battery_cell_voltages[5]    = {0,0,0,0,0};  // C1, C2, C3, C4, C5
float battery_cell_statistics[3]  = {0,0,0};      // MIN, MEAN, MAX
char  battery_cell_balancing[5]   = {0,0,0,0,0};  // C1, C2, C3, C4, C5


// LCD OBJECTS --------------------------------------------

gText menu_1;
gText menu_2;
gText menu_3;
gText menu_4;
gText menu_5;

gText bigNumerals;
gText header;

gText generalText_1;
gText generalText_2;
gText generalText_3;
gText generalText_4;
gText generalText_5;


// TIMING and BUTTON STUFF ------------------------------

IntervalTimer timer_250ms;
IntervalTimer button_repeat;

int TIMER_backlight           = TIMER_BACKLIGHT_RESET;
int TIMER_shutdown            = TIMER_SHUTDOWN_RESET;
int TIMER_onesecond           = 3;
int TIMER_exposure_countdown  = 0;


// SETUP ------------------------------------------------------

void setup(){
  // First, init the LCD library
  GLCD.Init(NON_INVERTED);
  GLCD.ClearScreen();
  delay(10);
  
  // Then begin init'ing things on the I2C bus  
  Wire.begin(); 
  
  MCP23107_init();
  MCP23017_write(EXP_PIN_BRIDGE_DISABLE, 1);
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 1);
  
  delay(10);
  BQ76920_init();
  MCP465x_init();
  
  // Set pin directions & stuff
  pinMode(PIN_BACKLIGHT, OUTPUT);
  pinMode(PIN_BUTTON_0,  INPUT);
  pinMode(PIN_BUTTON_1,  INPUT);
  pinMode(PIN_BUTTON_2,  INPUT);
  pinMode(PIN_WATCHDOG,  OUTPUT);
  MCP23017_set_pin_direction(EXP_PIN_CHARGE_SENSOR, 1); // Input

  // IRQs 
  attachInterrupt(PIN_BUTTON_0, readButtons, RISING);
  attachInterrupt(PIN_BUTTON_1, readButtons, RISING);
  attachInterrupt(PIN_BUTTON_2, readButtons, RISING);
  timer_250ms.begin(quarter_timer, 250000);
  
  // EEPROM Settings
  STATE_KVP = constrain(EEPROM.read(0)      , MIN_KVP, MAX_KVP);
  STATE_MAS = constrain(EEPROM.read(1) * 100, MIN_MAS, MAX_MAS);
  STATE_TIM = constrain(EEPROM.read(2)      , MIN_TIM, MAX_TIM);
  
//STATE_main_menu_selection   = constrain((EEPROM.read(3) & B00001111), 0, MMS_LIST_SIZE);
//STATE_sys_menu_selection    = constrain((EEPROM.read(3) >> 4)       , 0, SSS_LIST_SIZE);
  STATE_bluetooth_enabled     = constrain(EEPROM.read(4), 0, 1);
  STATE_auto_poweroff_enabled = constrain(EEPROM.read(5), 0, 1);
  
  // Set Boost Voltage
  MCP465x_set_wiper(BOOST, 100);
  
  // RFB = 470k - DONT GO ABOVE 128
  // 128 = 154V unloaded
  // 100 = 126V unloaded
  // 80  = 114V unloaded
  // 40  = 92V  unloaded
  // 20  = 84V  unloaded

  // RFB == 220k - DONT GO ABOVE 200
  // 20  = 40V unloaded
  // 40  = 45V unloaded
  // 80  = 54V unloaded
  // 100 = 60V unloaded
  // 120 = 70V unloaded
  // 140 = 80V unloaded
  // 160 = 100V unloaded

  Serial1.begin(115200);
  MCP23017_write(EXP_PIN_BT_ENABLE, 1);
    
  // Begin UI
  animation(ANIM_APERTURE);
  
  // Bluetooth Radio Configuration = SCRAPPED   
  set_Bluetooth_Name();  
  
  if(STATE_bluetooth_enabled)
    MCP23017_write(EXP_PIN_BT_ENABLE, 1);
  else
    MCP23017_write(EXP_PIN_BT_ENABLE, 0);
    
  draw_Menu();
}


// LOOP -------------------------------------------------------

void loop(){
  if(STATE_ui_button != 0){
    navigate_Menu();
    draw_Menu();
  }
  
  if(STATE_bluetooth_enabled){
    poll_Bluetooth();
  }
  
  if(FLAG_onesecond){
     FLAG_onesecond = 0;
     
     get_battery_info();
     balance_Cells();
     poll_Charger();
     protect_Cells();
     
     if(FLAG_charger_inserted){
       charge_Battery();
     };
  }
  
  if(FLAG_poweroff == 1){
    shutdown_System();
  }
 
  if(FLAG_initiate_countdown == 1){
    if(STATE_bluetooth_enabled) poll_Bluetooth();
    x_Ray();
  }
  
  if(FLAG_pack_dead == 1){
    animation(ANIM_BATTERY_DEAD);
    shutdown_System();
  }
}





