void readButtons(){
  
  analogWrite(PIN_BACKLIGHT, BACKLIGHT_BRIGHT);
  TIMER_backlight = TIMER_BACKLIGHT_RESET; 
  TIMER_shutdown  = TIMER_SHUTDOWN_RESET;
  
  /* LOW PASS FILTER */
  
  delay(10);
  
  int bit0 = digitalReadFast(PIN_BUTTON_0);
  int bit1 = digitalReadFast(PIN_BUTTON_1);
  int bit2 = digitalReadFast(PIN_BUTTON_2);
  
  int pressed_Button_A = bit0 | (bit1 << 1) | (bit2 << 2);
  
  delay(30);
  
  bit0 = digitalReadFast(PIN_BUTTON_0);
  bit1 = digitalReadFast(PIN_BUTTON_1);
  bit2 = digitalReadFast(PIN_BUTTON_2); 

  int pressed_Button_B = bit0 | (bit1 << 1) | (bit2 << 2);

  if(pressed_Button_B != pressed_Button_A){
    STATE_ui_button = buttonMap[0];
    return;
  }
  
  /* END LPF */
  
  if(FLAG_initiate_countdown == 1 && buttonMap[pressed_Button_A] != 'e'){
     STATE_ui_button = buttonMap[0];
     play_Sound(SOUND_MENU_NOT_AFFIRM);
     return;
  }
  
  else if(FLAG_charger_inserted){
     STATE_ui_button = buttonMap[0];
     play_Sound(SOUND_MENU_NOT_AFFIRM);
     return;
  }
  
  else{    
    STATE_ui_button = buttonMap[pressed_Button_A];    
    button_repeat.begin(ISR_button_repeat, 100000);
  }
}


void ISR_button_repeat(){
  readButtons();
      
  if(STATE_ui_button == buttonMap[0]){
    button_repeat.end();
  }
}
