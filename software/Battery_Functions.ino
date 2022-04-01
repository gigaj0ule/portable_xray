void charge_Battery(){
  
  animation(ANIM_CHARGER_INSERTED);
  
  FLAG_disable_poweroff = 1;
  
  GLCD.ClearScreen();
  GLCD.DrawBitmap(battery_charging,  0, 0);
  
  header.DefineArea(3, 2, 25, 1, Wendy3x5);
  header.SetFontColor(PIXEL_OFF);
  
  char FLAG_current_mode = 1;
  char FLAG_voltage_mode = 0;
  char FLAG_top_off_mode = 0;
 
  MCP23017_write(EXP_PIN_BATT_CURRENT_MODE, 1);
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 0);
 
  // Stage 1: Current mode -----------------------------
 
  while(FLAG_current_mode){
    
    get_battery_info();
    balance_Cells();
    poll_Charger();
    
    /* note, get_battery_info() is polled automagically by the ISR */ 
    /* note, balance_cells() ditto */
    
    header.ClearArea();
    header.print(STRING_CHARGE_STAGE1);
    
    if(battery_cell_statistics[MAX] > 4.195){
      FLAG_voltage_mode = 1;
      FLAG_current_mode = 0;  
    }
    
    if(FLAG_charger_inserted == 0){
      FLAG_voltage_mode = 0;
      FLAG_current_mode = 0;
      FLAG_top_off_mode = 0;
      goto killCharge;
    }
    
    draw_Battery_Panel();
    delay(500);
  }
  
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 1);
  
 // Stage 2: Voltage mode -----------------------------
 
  MCP23017_write(EXP_PIN_BATT_CURRENT_MODE,   0);
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 0);
  
  while(FLAG_voltage_mode){
    get_battery_info();
    balance_Cells();
    poll_Charger();
    
    header.ClearArea();
    header.print(STRING_CHARGE_STAGE2);
    
    if(battery_cell_statistics[MAX] > 4.2){
      FLAG_voltage_mode = 0;
      FLAG_top_off_mode = 1;  
    }
    
    if(FLAG_charger_inserted == 0){
      FLAG_voltage_mode = 0;
      FLAG_current_mode = 0;
      FLAG_top_off_mode = 0;
      goto killCharge;
    }
    
    draw_Battery_Panel();
    delay(500);
  }
  
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 1);
    
  // Stage 3: Top Off mode -----------------------------
 
  MCP23017_write(EXP_PIN_BATT_CURRENT_MODE,   0);
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 0);
  
  while(FLAG_top_off_mode){
    get_battery_info();
    balance_Cells();
    poll_Charger();
    
    header.ClearArea();
    header.print(STRING_CHARGE_STAGE3);
    
    /* toggly-doo */
    
    if(battery_cell_statistics[MAX] > 4.19){
      MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 1);
    }
    
    else if(battery_cell_statistics[MIN] < 4.1){
      MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 0); 
    }
    
    if(FLAG_charger_inserted == 0){
      FLAG_voltage_mode = 0;
      FLAG_current_mode = 0;
      FLAG_top_off_mode = 0; 
      goto killCharge; 
    }
    
    draw_Battery_Panel();
    delay(500);
  }

  // Clean up ----------------------------------
  killCharge:
  
  MCP23017_write(EXP_PIN_BATT_CHARGE_DISABLE, 1);

  FLAG_disable_poweroff  = 0;
  TIMER_shutdown         = TIMER_SHUTDOWN_RESET;
    
  animation(ANIM_CHARGER_REMOVED);
  draw_Menu();
}


void draw_Battery_Panel(){
  int LINE_HEIGHT = 9;
  int LINE_BASE   = 15;
  int INDENT      = 49;
  
  if(battery_cell_statistics[MIN] > 4.0){
    GLCD.DrawBitmap(batt_icon_4, 98, 15);
  }else if(battery_cell_statistics[MIN] > 3.7){
    GLCD.DrawBitmap(batt_icon_3, 98, 15);
  }else if(battery_cell_statistics[MIN] > 3.5){
    GLCD.DrawBitmap(batt_icon_2, 98, 15);
  }else if(battery_cell_statistics[MIN] > 3.2){
    GLCD.DrawBitmap(batt_icon_1, 98, 15);
  }else{
    GLCD.DrawBitmap(batt_icon_0, 98, 15);
  }
                  
  generalText_1.DefineArea(INDENT, LINE_BASE, 18, 1, Wendy3x5);
  generalText_1.print("C1: ");
  generalText_1.print(battery_cell_voltages[0], 3);
  generalText_1.print("V");
  if(battery_cell_balancing[0]) generalText_1.print("*"); else generalText_1.print(" ");
  
  generalText_2.DefineArea(INDENT, LINE_BASE + LINE_HEIGHT, 18, 1, Wendy3x5);
  generalText_2.print("C2: ");
  generalText_2.print(battery_cell_voltages[1], 3);
  generalText_2.print("V");
  if(battery_cell_balancing[1]) generalText_2.print("*"); else generalText_2.print(" ");
         
  generalText_3.DefineArea(INDENT, LINE_BASE + 2 * LINE_HEIGHT, 18, 1, Wendy3x5);
  generalText_3.print("C3: ");
  generalText_3.print(battery_cell_voltages[2], 3);
  generalText_3.print("V");
  if(battery_cell_balancing[2]) generalText_3.print("*"); else generalText_3.print(" ");
         
  generalText_4.DefineArea(INDENT, LINE_BASE + 3 * LINE_HEIGHT, 18, 1, Wendy3x5);
  generalText_4.print("C4: ");
  generalText_4.print(battery_cell_voltages[3], 3);
  generalText_4.print("V");
  if(battery_cell_balancing[3]) generalText_4.print("*"); else generalText_4.print(" ");
                  
  generalText_5.DefineArea(INDENT, LINE_BASE + 4 * LINE_HEIGHT, 18, 1, Wendy3x5);
  generalText_5.print("C5: ");
  generalText_5.print(battery_cell_voltages[4], 3);
  generalText_5.print("V");
  if(battery_cell_balancing[4]) generalText_5.print("*"); else generalText_5.print(" ");  
}


void balance_Cells(){ 
  for(int i = 0; i < 5; i++){
    if (battery_cell_voltages[i] > (battery_cell_statistics[MIN] + 0.008)){
      balance_cell(i, 1);
    }else{
      balance_cell(i, 0);
    }
  }
}


void protect_Cells(){
  if(battery_cell_statistics[MIN] < 2.8 && FLAG_charger_inserted == 0){ 
    FLAG_pack_dead = 1; 
  };
}


boolean poll_Charger(){ 
  // Sample twice for good measure 
  
  int old_charger_state = FLAG_charger_inserted;
  int charger_state_1   = MCP23017_read(EXP_PIN_CHARGE_SENSOR);
  int charger_state_2   = MCP23017_read(EXP_PIN_CHARGE_SENSOR);

  if(charger_state_1 == charger_state_2){
    if (charger_state_1 == 1) FLAG_charger_inserted = 1;
    else FLAG_charger_inserted = 0;
    return charger_state_1;
  }else{
    FLAG_charger_inserted = old_charger_state;
    return old_charger_state;
  }
}
