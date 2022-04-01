void BQ76920_init(){
  // The BQ76920 Needs a 2ms pulse to start
  MCP23017_write(EXP_PIN_BATTERY_MON_ENABLE, 1);
  delay(2);
  MCP23017_write(EXP_PIN_BATTERY_MON_ENABLE, 0);
  delay(2);
  
  Wire.beginTransmission(BATTERY_MONITOR_ADDRESS);
  Wire.write(0x0B);
  Wire.write(0x19);
  Wire.endTransmission();
}


void get_battery_info(){
  Wire.beginTransmission(BATTERY_MONITOR_ADDRESS);
  Wire.write(0x0C);
  Wire.endTransmission(); 
  
  Wire.requestFrom(BATTERY_MONITOR_ADDRESS, 10);
  
  char i2c_buffer[10];
  
  for(int i = 0; i < 5; i++){
    char high_byte = Wire.read();
    char low_byte  = Wire.read();
        
    int raw_value = low_byte | (high_byte << 8);
    
    battery_cell_voltages[i] = (float)raw_value * 0.000382;
  }
  
  cell_Statistics();
}


void cell_Statistics(){
  //battery_cell_statistcs[] = {min, max, mean}
  
  battery_cell_statistics[MIN] = 5;
  battery_cell_statistics[MAX] = 0;
    
  for(int i = 0; i < 5; i++){
     if(battery_cell_statistics[MIN] > battery_cell_voltages[i])
       battery_cell_statistics[MIN] = battery_cell_voltages[i];
         
     if(battery_cell_statistics[MAX] < battery_cell_voltages[i])
       battery_cell_statistics[MAX] = battery_cell_voltages[i];
  }
    
  battery_cell_statistics[MEAN] = 
    battery_cell_voltages[0] +
    battery_cell_voltages[1] +
    battery_cell_voltages[2] +
    battery_cell_voltages[3] +
    battery_cell_voltages[4];
  
  battery_cell_statistics[MEAN] = battery_cell_statistics[MEAN] / 5;
}


void balance_cell(int cell, int state){
  
  Wire.beginTransmission(BATTERY_MONITOR_ADDRESS);
  Wire.write(0x01);
  Wire.endTransmission(); 
  
  Wire.requestFrom(BATTERY_MONITOR_ADDRESS, 1);

  char bal_Buffer = Wire.read();
  bitWrite(bal_Buffer, cell, state);

  Wire.beginTransmission(BATTERY_MONITOR_ADDRESS);
  Wire.write(0x01);
  Wire.write(bal_Buffer);
  Wire.endTransmission(); 
  
  battery_cell_balancing[cell] = state;
}
