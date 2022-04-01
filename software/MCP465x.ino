void MCP465x_init(){
  Wire.beginTransmission(DIGITAL_POT_ADDRESS); 
  Wire.endTransmission(); 
}


void MCP465x_set_wiper(int wiper, int value){
      
  /*command byte struct: 
    
  Device address                  Register Add  | Cmd     | Data
  [0][1][0][1][A2][A1][A0][0] - [A1][A2][A3][A4] [0][0][x] [D8] - [D7][D6][D4][D3][D2][D1][D0]
  */
    
  if(wiper == 0){
    Wire.beginTransmission(0x29);
    Wire.write(B00000000);
    Wire.write(value);
    Wire.write(0);
    Wire.endTransmission(); 
  }
  else{
    Wire.beginTransmission(0x29);
    Wire.write(B00010000);
    Wire.write(value);
    Wire.write(0);
    Wire.endTransmission();     
  }
}
