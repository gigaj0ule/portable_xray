void quarter_timer(){
  
  FLAG_watchdog = !FLAG_watchdog;
  digitalWriteFast(PIN_WATCHDOG, FLAG_watchdog);

  if(TIMER_onesecond > 0){
    TIMER_onesecond --;
  }else{
    TIMER_onesecond = 3;
    FLAG_onesecond = 1;
      
    if(FLAG_initiate_countdown == 1){ 
      if(TIMER_exposure_countdown > 0){
        TIMER_exposure_countdown--;
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        
        generalText_3.ClearArea();
        generalText_3.print(STRING_EXPOSE_TEXT5);
        generalText_3.print(TIMER_exposure_countdown);
      }
      
      else{
        FLAG_initiate_countdown = 0;
        FLAG_initiate_exposure  = 1;
      }
    }
    
    if(STATE_auto_poweroff_enabled && FLAG_disable_poweroff == 0){
         
      if(TIMER_shutdown > 0){
        TIMER_shutdown --;
      }else{
        FLAG_poweroff = 1;
      }
    }
    
    if(TIMER_backlight > 0){
      TIMER_backlight --;
      analogWrite(PIN_BACKLIGHT, BACKLIGHT_BRIGHT);
    }else{
      analogWrite(PIN_BACKLIGHT, BACKLIGHT_DIM);
    }
  }
  
  if(FLAG_initiate_exposure == 0){
   // get_battery_info();
   // balance_Cells();
   // poll_Charger();
   // protect_Cells();
  }
}


void shutdown_System(){
  
  EEPROM.write(0, STATE_KVP);
  EEPROM.write(1, STATE_MAS / 100);
  EEPROM.write(2, STATE_TIM);
  EEPROM.write(3, (STATE_main_menu_selection & B00001111) | (STATE_sys_menu_selection << 4));
  EEPROM.write(4, STATE_bluetooth_enabled);
  EEPROM.write(5, STATE_auto_poweroff_enabled);
  
  for(int i = 0; i < 5; i++){
    balance_cell(i, 0); 
  }
  
  timer_250ms.end();
  
  while(1){
    delay(1); 
  }
}

