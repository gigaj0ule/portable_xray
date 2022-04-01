void poll_Bluetooth(){
  
  if(Serial1.available()){
    TIMER_shutdown  = TIMER_SHUTDOWN_RESET;
    TIMER_backlight = TIMER_BACKLIGHT_RESET; 
      
    char cmd = Serial1.read();

    // SET STATEMENTS ----------------------------------------
   
    if (cmd == '#'){
      char statement = Serial1.read();
      
      if(statement == 'K'){
        char number = Serial1.read();
       
        if(number > MIN_KVP && number < MAX_KVP){
          serial_Affirm();
                    
          STATE_KVP = number;
          STATE_main_menu_selection = MMS_ENERGY;
          draw_Menu();
          return;
        }else{
          serial_Not_Affirm();
          return;
        }
      }
      
      if(statement == 'T'){
        char number = Serial1.read();
       
        if(number > MIN_TIM && number < MAX_TIM){
          serial_Affirm();

          STATE_TIM = number;
          STATE_main_menu_selection = MMS_TIMER;
          draw_Menu();
          return;
        }else{
          serial_Not_Affirm();
          return;
        }
      }
     
      if(statement == 'E'){
        char number = Serial1.read();
        
        number = number * 100;
       
        if(number > MIN_MAS && number < MAX_MAS){
          serial_Affirm();
                    
          STATE_MAS = number;
          STATE_main_menu_selection = MMS_EXPOSURE;
          draw_Menu();
          return;
        }else{
          serial_Not_Affirm();
          return;
        } 
      }
    
      if(statement == 'X'){
        STATE_main_menu_selection = MMS_XRAY;
                  
        if(FLAG_initiate_countdown == 0){
          Serial1.print("A"); 
          TIMER_exposure_countdown = STATE_TIM;            
          draw_Menu();
          
          play_Sound(SOUND_XRAY);
          FLAG_initiate_countdown = 1;
        }else{
          Serial1.print("A"); 
          FLAG_initiate_countdown = 0;
        }
      }
      
      if(statement == 'S'){
        serial_Affirm();
        FLAG_poweroff = 1;
      }
    }
    
    // GET STATEMENTS ----------------------------------

    else if (cmd == '$'){
      char statement = Serial1.read();
      
      if(statement == 'K'){
        Serial1.print(STATE_KVP);
      }
      
      else if(statement == 'T'){
        Serial1.print(STATE_TIM);
      }
      
      else if(statement == 'E'){
        Serial1.print(STATE_MAS / 100);
      }
    }
  
    else{
      serial_Not_Affirm();
    }
  }
} 

void serial_Affirm(){
  serial_Flush();
  play_Sound(SOUND_MENU_AFFIRM);
  Serial1.print("A"); 
}

void serial_Not_Affirm(){
  serial_Flush();
  play_Sound(SOUND_MENU_NOT_AFFIRM);
  Serial1.print("N"); 
}

void serial_Flush(){
  for(int i = 0; i < 64; i++){
    Serial1.read();
  }
}

void set_Bluetooth_Name(){
  Serial1.print("$$$");
  delay(50);
  Serial1.print("SN,");
  Serial1.print(STRING_DEVICE_NAME);
  Serial1.write(13);
  delay(30);
  Serial1.print("R,1");
  Serial1.write(13);
  serial_Flush();
}

boolean check_Bluetooth_Status(){
  Serial1.print("$$$");
  delay(20);
  serial_Flush();

  Serial1.print("GK");
  Serial1.write(13);
  delay(20);
  
  if(Serial1.read() == '1'){
    Serial1.print("---");
    Serial1.write(13);
    serial_Flush();
    return 1;
  }else{
    Serial1.print("---");
    Serial1.write(13);
    serial_Flush();
    return 0; 
  }
}
