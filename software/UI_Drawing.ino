void draw_Menu(){

  #define MENU_LINE_HEIGHT 10
  #define MENU_MARGIN_LEFT 3   
  #define MENU_MARGIN_TOP  12
  
  GLCD.ClearScreen();
  GLCD.DrawBitmap(frameset,  0, 0);
  
  if(STATE_main_menu_selection == MMS_SYSTEM){
    
    if(STATE_sys_menu_selection == SSS_BLUETOOTH)
      GLCD.DrawBitmap(bluetooth, 0, 0);
      
    else if(STATE_sys_menu_selection == SSS_SHUTDOWN)
      GLCD.DrawBitmap(poweroff,  0, 0);
  }
  
  else if(STATE_main_menu_selection == MMS_XRAY){
      GLCD.DrawBitmap(expose, 0, 0);
  }  
  
  menu_1.DefineArea(MENU_MARGIN_LEFT, MENU_MARGIN_TOP + 0 * MENU_LINE_HEIGHT, 6, 1, SystemFont5x7);
  menu_2.DefineArea(MENU_MARGIN_LEFT, MENU_MARGIN_TOP + 1 * MENU_LINE_HEIGHT, 6, 1, SystemFont5x7);
  menu_3.DefineArea(MENU_MARGIN_LEFT, MENU_MARGIN_TOP + 2 * MENU_LINE_HEIGHT, 6, 1, SystemFont5x7);
  menu_4.DefineArea(MENU_MARGIN_LEFT, MENU_MARGIN_TOP + 3 * MENU_LINE_HEIGHT, 6, 1, SystemFont5x7);
  menu_5.DefineArea(MENU_MARGIN_LEFT, MENU_MARGIN_TOP + 4 * MENU_LINE_HEIGHT, 6, 1, SystemFont5x7);

  header.DefineArea(3, 2, 28, 1, Wendy3x5);
  header.SetFontColor(PIXEL_OFF);

  if(STATE_main_menu_selection == MMS_ENERGY)
    menu_1.SetFontColor(PIXEL_OFF);
  else
    menu_1.SetFontColor(PIXEL_ON);
    
  if(STATE_main_menu_selection == MMS_EXPOSURE)
    menu_2.SetFontColor(PIXEL_OFF);
  else
    menu_2.SetFontColor(PIXEL_ON);
  
  if(STATE_main_menu_selection == MMS_TIMER)
    menu_3.SetFontColor(PIXEL_OFF);
  else
    menu_3.SetFontColor(PIXEL_ON);
  
  if(STATE_main_menu_selection == MMS_XRAY)
    menu_4.SetFontColor(PIXEL_OFF);
  else
    menu_4.SetFontColor(PIXEL_ON);  
  
  if(STATE_main_menu_selection == MMS_SYSTEM)
    menu_5.SetFontColor(PIXEL_OFF);
  else
    menu_5.SetFontColor(PIXEL_ON);
   
  menu_1.print(STRING_KVP_MENU);
  menu_2.print(STRING_MAS_MENU);
  menu_3.print(STRING_TIM_MENU);
  menu_4.print(STRING_EXPOSE_MENU);
  menu_5.print(STRING_SYSTEM_MENU);
  
  if(STATE_main_menu_selection == MMS_ENERGY ||
     STATE_main_menu_selection == MMS_EXPOSURE ||
     STATE_main_menu_selection == MMS_TIMER){
  
     bigNumerals.DefineArea(52, 16, 4, 1, lcdnums14x24); 
     bigNumerals.ClearArea();
  
     generalText_1.DefineArea(53, 50, 18, 1, Wendy3x5);
     generalText_1.ClearArea();
  }
  
  if(STATE_main_menu_selection == MMS_ENERGY){
    header.print(STRING_KVP_HEADER);
    generalText_1.print(STRING_KVP_UNITS);
    bigNumerals.print(STATE_KVP, DEC);
  }
  
  if(STATE_main_menu_selection == MMS_EXPOSURE){
    header.print(STRING_MAS_HEADER);
    generalText_1.print(STRING_MAS_UNITS);
    bigNumerals.print(STATE_MAS, DEC);
  }
  
  if(STATE_main_menu_selection == MMS_TIMER){
    header.print(STRING_TIM_HEADER);
    generalText_1.print(STRING_TIM_UNITS);
    bigNumerals.print(STATE_TIM, DEC);
  }
  
  if(STATE_main_menu_selection == MMS_XRAY){
    header.print(STRING_EXPOSE_HEADER);
    
    #define MMS_XRAY_LINE_HEIGHT 10
       
    generalText_1.DefineArea(78, 19, 15, 1, Wendy3x5);
    generalText_1.print(STRING_EXPOSE_TEXT1);
    
    generalText_2.DefineArea(78, 19 + MMS_XRAY_LINE_HEIGHT, 15, 1, Wendy3x5);
    generalText_3.DefineArea(53, 50, 18, 1, Wendy3x5);
    
    if(FLAG_initiate_countdown == 0){
       generalText_2.print(STRING_EXPOSE_TEXT2);

       generalText_3.print(STATE_TIM, DEC);
       generalText_3.print(STRING_EXPOSE_TEXT3);
    }else{
       generalText_2.print(STRING_EXPOSE_TEXT4);       
    }
  }
  
  
  if(STATE_main_menu_selection == MMS_SYSTEM){
     if(STATE_sys_menu_selection == SSS_SHUTDOWN){
       header.print(STRING_SYSTEM_POWEROFF_HEADER);
       
       #define SHUTDOWN_LINE_HEIGHT 10
       
       generalText_1.DefineArea(75, 19, 18, 1, Wendy3x5);
       generalText_1.print(STRING_SYSTEM_TEXT1);
       
       generalText_2.DefineArea(75, 19 + SHUTDOWN_LINE_HEIGHT, 18, 1, Wendy3x5);
       generalText_2.print(STRING_SYSTEM_TEXT2);
       
       generalText_3.DefineArea(50, 50, 18, 1, Wendy3x5);
       generalText_3.print(STRING_SYSTEM_AUTOFF);
       
       if(STATE_auto_poweroff_enabled)
         generalText_3.print(STRING_YES);
       else
         generalText_3.print(STRING_NO);
     }
     
     
     if(STATE_sys_menu_selection == SSS_BLUETOOTH){
       header.print(STRING_SYSTEM_BLUETOOTH_HEADER);
       
       int LINE_HEIGHT = 14;
       
       generalText_1.DefineArea(69, 23, 18, 1, System5x7);
       
       if(STATE_bluetooth_enabled){
         MCP23017_write(EXP_PIN_BT_ENABLE, 1);
         generalText_1.print(STRING_BTENABLED);
       }
       else{
         MCP23017_write(EXP_PIN_BT_ENABLE, 0);
         generalText_1.print(STRING_BTDISABLED);
       }

       if(STATE_bluetooth_enabled){ 
         generalText_2.DefineArea(50, 44, 18, 1, Wendy3x5);
         generalText_2.print(STRING_BTID);
         generalText_2.print(STRING_DEVICE_NAME);
         
         generalText_3.DefineArea(50, 44 + 9, 18, 1, Wendy3x5);
         
         while(STATE_ui_button == 0){       
           generalText_3.ClearArea();
           generalText_3.print(STRING_CONNECTED);

           boolean bt_Status = check_Bluetooth_Status();
           
           if(bt_Status == 1){
             generalText_3.print(STRING_YES);
           }else{
             generalText_3.print(STRING_NO);
           }
           
           delay(250);
           
           if(FLAG_charger_inserted != 0){
             break;
           }
         
           if(FLAG_poweroff != 0){
             break;
           }
         }
       }
     }
     
     
     if(STATE_sys_menu_selection == SSS_BATTERY){
       header.print(STRING_SYSTEM_BATTERY_HEADER);
       
       int LINE_HEIGHT = 9;
       int LINE_BASE   = 15;
       int INDENT      = 49;
       
       while(STATE_ui_button == 0){       
         get_battery_info();
         poll_Charger();
         balance_Cells();
         protect_Cells();
         draw_Battery_Panel();
         
         if(FLAG_charger_inserted != 0){
           break;
         }
         
         if(FLAG_poweroff != 0){
           break;
         }
         
         delay(250);
       }
     }
  }
}
