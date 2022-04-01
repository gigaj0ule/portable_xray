void MCP23107_init(){
  Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();
   
  Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
  Wire.write(0x01); // IODIRB register
  Wire.write(0x00); // set all of port B to outputs
  Wire.endTransmission(); 
}


void MCP23017_set_pin_direction(int pin, int dir){
  
  if(pin > 7){     // IODIRB Register
  
    char IODIRB_Buffer;

    Wire.beginTransmission(I2C_EXPANDER_ADDRESS); 
    Wire.write(0x10); 
    Wire.endTransmission(); 
    Wire.requestFrom(I2C_EXPANDER_ADDRESS, 1);
    IODIRB_Buffer = Wire.read();
    
    pin = pin - 8;
    
    bitWrite(IODIRB_Buffer, pin, dir);
    
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x01);
    Wire.write(IODIRB_Buffer);
    Wire.endTransmission(); 
  }
  
  else{  // IODIRA register
 
    char IODIRA_Buffer;
   
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x00); 
    Wire.endTransmission(); 
    Wire.requestFrom(I2C_EXPANDER_ADDRESS, 1);
    IODIRA_Buffer = Wire.read();
    
    bitWrite(IODIRA_Buffer, pin, dir);

    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x00);
    Wire.write(IODIRA_Buffer);
    Wire.endTransmission();
  }
}


void MCP23017_write(int pin, int state){
  
  if(pin > 7){
    char GPIOB_Buffer;
     
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x13);
    Wire.endTransmission(); 
    Wire.requestFrom(I2C_EXPANDER_ADDRESS, 1);
    GPIOB_Buffer = Wire.read();
    
    pin = pin - 8;
    
    bitWrite(GPIOB_Buffer, pin, state);
    
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x13);
    Wire.write(GPIOB_Buffer);
    Wire.endTransmission(); 
  }
  
  else{
    char GPIOA_Buffer;
    
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x12);
    Wire.endTransmission(); 
    Wire.requestFrom(I2C_EXPANDER_ADDRESS, 1);
    GPIOA_Buffer = Wire.read();
    
    bitWrite(GPIOA_Buffer, pin, state);

    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x12);
    Wire.write(GPIOA_Buffer);
    Wire.endTransmission();
  }
}


boolean MCP23017_read(int pin){
  
  if(pin > 7){
    char GPIOB_Buffer;
     
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x13);
    Wire.endTransmission(); 
    Wire.requestFrom(I2C_EXPANDER_ADDRESS, 1);
    GPIOB_Buffer = Wire.read();
    
    pin = pin - 8;
    
    return bitRead(GPIOB_Buffer, pin);
  }
  
  else{
    char GPIOA_Buffer;
    
    Wire.beginTransmission(I2C_EXPANDER_ADDRESS);
    Wire.write(0x12);
    Wire.endTransmission(); 
    Wire.requestFrom(I2C_EXPANDER_ADDRESS, 1);
    GPIOA_Buffer = Wire.read();
    
    return bitRead(GPIOA_Buffer, pin);
  }
}
