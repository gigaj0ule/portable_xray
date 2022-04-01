void navigate_Menu(){
  
  int ui_button_buffer = STATE_ui_button;
  STATE_ui_button = 0;
  
  if(ui_button_buffer == 'u'){
    
    if(STATE_main_menu_selection > 0){
      STATE_main_menu_selection --;
      play_Sound(SOUND_MENU_AFFIRM);
      return;
    }
    
    else if(STATE_main_menu_selection == 0){
      play_Sound(SOUND_MENU_NOT_AFFIRM);
      return;
    }
  }
  
  if(ui_button_buffer == 'd'){
    
    if(STATE_main_menu_selection < MMS_LIST_SIZE){
      STATE_main_menu_selection ++;
      play_Sound(SOUND_MENU_AFFIRM);
      return;
    }
    
    else if(STATE_main_menu_selection == 0){
      play_Sound(SOUND_MENU_NOT_AFFIRM);
      return;
    }
  }
  
  
  if(STATE_main_menu_selection == MMS_SYSTEM){
    if(ui_button_buffer == 'l'){
      
      if(STATE_sys_menu_selection > 0){
        STATE_sys_menu_selection --;
        play_Sound(SOUND_MENU_AFFIRM);
        return;
      }
      
      else if(STATE_sys_menu_selection == 0){
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        return;
      }
    }
    
    
    if(ui_button_buffer == 'r'){
      
      if(STATE_sys_menu_selection < SSS_LIST_SIZE){
        STATE_sys_menu_selection ++;
        play_Sound(SOUND_MENU_AFFIRM);
        return;
      }
      
      else if(STATE_sys_menu_selection == 0){
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        return;
      }
    }
  }
  
  
  if(STATE_main_menu_selection == MMS_ENERGY){
    if(ui_button_buffer == 'a'){
      if(STATE_KVP < MAX_KVP){
        STATE_KVP++;
        play_Sound(SOUND_MENU_AFFIRM);
        return;
      }else{
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        return;
      }
    }
     
    if(ui_button_buffer == 'b'){
      if(STATE_KVP > MIN_KVP){
        STATE_KVP--;
        play_Sound(SOUND_MENU_AFFIRM);
        return;
      }else{
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        return;
      }
    }
  }
 
 
  if(STATE_main_menu_selection == MMS_EXPOSURE){
    if(ui_button_buffer == 'a'){
      if(STATE_MAS < MAX_MAS){
        STATE_MAS += 100;
        play_Sound(SOUND_MENU_AFFIRM);
        return;
      }else{
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        return;
      }
    }
     
    if(ui_button_buffer == 'b'){
      if(STATE_MAS > MIN_MAS){
        STATE_MAS -= 100;
        play_Sound(SOUND_MENU_AFFIRM);
        return;
      }else{
        play_Sound(SOUND_MENU_NOT_AFFIRM);
        return;
      }
    }
  }
  
  if(STATE_main_menu_selection == MMS_TIMER){
    if(ui_button_buffer == 'a'){
      if(STATE_TIM < MAX_TIM){
        STATE_TIM++;
        play_Sound(SOUND_MENU_AFFIRM); 
        return;
      }else{
        play_Sound(SOUND_MENU_NOT_AFFIRM); 
        return;
      }
    }
     
    if(ui_button_buffer == 'b'){
      if(STATE_TIM > MIN_TIM){
        STATE_TIM--;
        play_Sound(SOUND_MENU_AFFIRM); 
        return;
      }else{
        play_Sound(SOUND_MENU_NOT_AFFIRM); 
        return;
      }
    }
  }
  
  if(STATE_main_menu_selection == MMS_XRAY){
    if(ui_button_buffer == 'e'){
       if(FLAG_initiate_countdown == 0){
         TIMER_exposure_countdown = STATE_TIM;
         
         play_Sound(SOUND_XRAY); 
         delay(100);
         
         FLAG_initiate_countdown = 1;
         return;
       }
       
       else{
         cancel_Xray();
         return; 
       }
    }
  }
       
  if(STATE_main_menu_selection == MMS_SYSTEM){
    
    if(STATE_sys_menu_selection  == SSS_SHUTDOWN){
      if(ui_button_buffer == 'e'){
         FLAG_poweroff = 1;
         play_Sound(SOUND_MENU_AFFIRM); 
         return;
      }
    }
    
    if(STATE_sys_menu_selection  == SSS_BLUETOOTH){
      if(ui_button_buffer == 'a'){
        if(STATE_bluetooth_enabled == 0){
          STATE_bluetooth_enabled = 1;
          play_Sound(SOUND_MENU_AFFIRM);
          return;
        }
        else if(STATE_bluetooth_enabled == 1){
          play_Sound(SOUND_MENU_NOT_AFFIRM);
          return;
        }
      }
      
      else if(ui_button_buffer == 'b'){
        if(STATE_bluetooth_enabled == 1){
          STATE_bluetooth_enabled = 0;
          play_Sound(SOUND_MENU_AFFIRM);
          return;
        }
        else if(STATE_bluetooth_enabled == 0){
          play_Sound(SOUND_MENU_NOT_AFFIRM);
          return;
        }
      }
    }
    
    if(STATE_sys_menu_selection  == SSS_SHUTDOWN){
      if(ui_button_buffer == 'a'){
        if(STATE_auto_poweroff_enabled == 0){
          STATE_auto_poweroff_enabled = 1;
          play_Sound(SOUND_MENU_AFFIRM);
          STATE_ui_button = 0;
          return;
        }
        else if(STATE_auto_poweroff_enabled == 1){
          play_Sound(SOUND_MENU_NOT_AFFIRM);
          return;
        }
      }
      
      else if(ui_button_buffer == 'b'){
        if(STATE_auto_poweroff_enabled == 1){
          STATE_auto_poweroff_enabled = 0;
          play_Sound(SOUND_MENU_AFFIRM);
          return;
        }
        else if(STATE_auto_poweroff_enabled == 0){
          play_Sound(SOUND_MENU_NOT_AFFIRM);
          return;
        }
      }
    } 
  } 

  play_Sound(SOUND_MENU_NOT_AFFIRM);
}




