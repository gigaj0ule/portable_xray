void animation(int animation_index){
  
  if(animation_index == ANIM_CHARGER_INSERTED){
    
    GLCD.ClearScreen();
    GLCD.DrawBitmap(charger_inserted, 0, 0);
    header.DefineArea(3, 2, 25, 1, Wendy3x5);
    header.SetFontColor(PIXEL_OFF);
    header.print(STRING_CHARGER_DETECTED);
    
    play_Sound(SOUND_CHARGER_INSERTED);
    
    delay(2000);
    
    return;
  }
  
  if(animation_index == ANIM_CHARGER_REMOVED){
    
    GLCD.ClearScreen();
    GLCD.DrawBitmap(charger_removed, 0, 0);
    header.DefineArea(3, 2, 25, 1, Wendy3x5);
    header.SetFontColor(PIXEL_OFF);
    header.print(STRING_CHARGER_REMOVED);
    
    play_Sound(SOUND_CHARGER_REMOVED);
    
    delay(2000);
    
    return;
  }
  
  
  if(animation_index == ANIM_APERTURE){
    
    analogWrite(PIN_BACKLIGHT, 0);    
    
    GLCD.ClearScreen();
    GLCD.DrawBitmap(aperture, 0, 0);
    
    play_Sound(SOUND_WAKEUP);
    
    for(int i = 0; i < BACKLIGHT_BRIGHT; i ++){
      delay(10);
      analogWrite(PIN_BACKLIGHT, i);
    }
        
    delay(1000);
    
    return;
  }
  
  if(animation_index == ANIM_BATTERY_DEAD){
    
    GLCD.ClearScreen();
    GLCD.DrawBitmap(battery_empty, 0, 0);
    header.DefineArea(3, 2, 25, 1, Wendy3x5);
    header.SetFontColor(PIXEL_OFF);
    header.print(STRING_BATTERY_DEAD);
    
    play_Sound(SOUND_BATTERY_DEAD);
    
    delay(2000);
    
    return;
  }
}



void play_Sound(int sound){
  
  if(sound == SOUND_MENU_AFFIRM){
    tone(PIN_BUZZER, NOTE_A5, 20);
    return;
  } 
 
  if(sound == SOUND_MENU_NOT_AFFIRM){
    tone(PIN_BUZZER, NOTE_A4, 20);
    return;
  }
  
  if(sound == SOUND_CHARGER_INSERTED){
    tone(PIN_BUZZER, NOTE_A4);
    delay(100);
    tone(PIN_BUZZER, NOTE_A3);
    delay(100);
    tone(PIN_BUZZER, NOTE_A5);
    delay(100);
    noTone(PIN_BUZZER);
  }
  
  if(sound == SOUND_CHARGER_REMOVED){
    tone(PIN_BUZZER, NOTE_A5);
    delay(100);
    tone(PIN_BUZZER, NOTE_A4);
    delay(100);
    tone(PIN_BUZZER, NOTE_A3);
    delay(100);
    noTone(PIN_BUZZER);
  }
  
  if(sound == SOUND_WAKEUP){
    tone(PIN_BUZZER, NOTE_A3);
    delay(100);
    tone(PIN_BUZZER, NOTE_A5);
    delay(100);
    noTone(PIN_BUZZER);
  }
 
  if(sound == SOUND_XRAY){
    tone(PIN_BUZZER, NOTE_A4);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
    
    tone(PIN_BUZZER, NOTE_A4);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
    
    tone(PIN_BUZZER, NOTE_A5);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
  }
  
  if(sound == SOUND_CANCEL_XRAY){
    tone(PIN_BUZZER, NOTE_A5);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
    
    tone(PIN_BUZZER, NOTE_A5);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
    
    tone(PIN_BUZZER, NOTE_A4);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
  }
  
  if(sound == SOUND_BATTERY_DEAD){
    tone(PIN_BUZZER, NOTE_A4);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
    
    tone(PIN_BUZZER, NOTE_A4);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
    
    tone(PIN_BUZZER, NOTE_A4);
    delay(50);
    noTone(PIN_BUZZER);
    delay(50);
  } 
}
