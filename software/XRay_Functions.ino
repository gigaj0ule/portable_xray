void x_Ray(){
  
  // Do nothing until T-Minus 2 seconds
 
  if(FLAG_initiate_countdown == 1 && TIMER_exposure_countdown < 2){
    
    int heater_val = map(STATE_KVP, MIN_KVP, MAX_KVP, MAX_CATHODE_VAL, MIN_CATHODE_VAL);
    MCP465x_set_wiper(HEATER, heater_val);
      
    MCP23017_write(EXP_PIN_CATHODE_ENABLE, 1);
        
    while(FLAG_initiate_exposure == 0){
      if(STATE_ui_button == 'e' || FLAG_initiate_countdown == 0){
        cancel_Xray();
        draw_Menu();
        return;
      }
      if(STATE_bluetooth_enabled) poll_Bluetooth();
      delay(1);
    }
        
    if(FLAG_initiate_exposure == 1){
      GLCD.ClearScreen();
      GLCD.DrawBitmap(exposing,  0, 0);
      
      if(STATE_bluetooth_enabled) Serial1.print("z");
      tone(PIN_BUZZER, 220);
      
      if(NO_X_RAY){ 
        MCP23017_write(EXP_PIN_BIG_BOOST_ENABLE, 0);
        delay(100);
        MCP23017_write(EXP_PIN_BRIDGE_DISABLE, 1);
      }else{
        MCP23017_write(EXP_PIN_BIG_BOOST_ENABLE, 1);
        delay(100);
        MCP23017_write(EXP_PIN_BRIDGE_DISABLE, 0); 
      }
                      
      for(int i = 0; i <= STATE_MAS; i += 100){
        delay(100);
      }
        
      MCP23017_write(EXP_PIN_BIG_BOOST_ENABLE, 0);
      MCP23017_write(EXP_PIN_BRIDGE_DISABLE, 1);
  
      if(STATE_bluetooth_enabled) Serial1.print("Z");        
      noTone(PIN_BUZZER);
          
      MCP23017_write(EXP_PIN_CATHODE_ENABLE, 0);
          
      FLAG_initiate_exposure  = 0;
      FLAG_initiate_countdown = 0;
         
      // The screen someties needs a reset after an x-ray, heh...
      GLCD.Init(NON_INVERTED);
      draw_Menu();
          
      generalText_3.ClearArea();
      generalText_3.print(STRING_EXPOSE_TEXT6);
    } 
    
    FLAG_initiate_countdown == 0;
    FLAG_initiate_exposure  == 0;
  }
}


void cancel_Xray(){
  FLAG_initiate_countdown = 0;
  FLAG_initiate_exposure = 0;
  MCP23017_write(EXP_PIN_BIG_BOOST_ENABLE, 0);
  MCP23017_write(EXP_PIN_BRIDGE_DISABLE, 1);
  MCP23017_write(EXP_PIN_CATHODE_ENABLE, 0);
   
  play_Sound(SOUND_CANCEL_XRAY); 
  delay(100);
}
