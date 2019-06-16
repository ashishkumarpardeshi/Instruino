
//int x, y;  

void touch_read()
{ 
  x = -1;
  y = -1;
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  while(ts.dataAvailable())        
  {
    ts.read();                      
    x = ts.getX();                 
    y = ts.getY(); 
    Serial.print("x = ");   
    Serial.print(x);
    Serial.print(" y = ");
    Serial.println(y);
  } 
} 

int touch_result()
{
  int select_home = 0;
  if((x >= 18 && x <= 173) && (y >= 80 && y<= 111))
    {
      select_home = 1;
      tft.fillRect(10,75,165,45,ILI9341_GREEN);
      tft.setCursor(45,90);
      tft.print("pH Probe");
      //delay(2);
      tft.fillRect(10,75,165,45,ILI9341_ORANGE);
      tft.setCursor(45,90);
      tft.print("pH Probe");
    }
    if((x >= 18 && x <= 173) && (y >= 137 && y<= 168))
    {
      select_home = 2;
      tft.fillRect(10,130,165,45,ILI9341_GREEN);
      tft.setCursor(33,145);
      tft.print("Temp Probe");
      //delay(2);
      tft.fillRect(10,130,165,45,ILI9341_PINK);
      tft.setCursor(33,145);
      tft.print("Temp Probe");
      
    }
    if((x >= 18 && x <= 173) && (y >= 190 && y<= 220))
    {
      select_home = 3;
      tft.fillRect(10,185,165,45,ILI9341_GREEN);
      tft.setCursor(40,200);
      tft.print("Turbidity");
      //delay(2);
      tft.fillRect(10,185,165,45,ILI9341_BLUE);
      tft.setCursor(40,200);
      tft.print("Turbidity");
    }
    
    if((x >= 201 && x <= 310) && (y >= 80 && y<= 111))
    {
      select_home = 4;
      tft.fillRect(192,75,120,45,ILI9341_GREEN);
      tft.setCursor(233,90);
      tft.print("WiFi");
      //delay(1);
      tft.fillRect(192,75,120,45,ILI9341_WHITE);
      tft.setCursor(233,90);
      tft.print("WiFi");
    }
    if((x >= 201 && x <= 310) && (y >= 137 && y<= 168))
    {
      select_home = 5;
      tft.fillRect(192,130,120,45,ILI9341_GREEN);
      tft.setCursor(198,145);
      tft.print("Bluetooth");
      delay(1);
      tft.fillRect(192,130,120,45,ILI9341_WHITE);
      tft.setCursor(198,145);
      tft.print("Bluetooth");
    }
    if((x >= 201 && x <= 310) && (y >= 190 && y<= 220))
    {
      select_home = 6;
      tft.fillRect(192,185,120,45,ILI9341_GREEN);
      tft.setCursor(211,200);
      tft.print("SD Card");
      delay(1);
      tft.fillRect(192,185,120,45,ILI9341_WHITE);
      tft.setCursor(211,200);
      tft.print("SD Card");
    }

    if(select_home >= 1 && select_home <= 6)
    {
      imp_flag();
      wait_screen = 1;
    }
  
  return select_home;
}



/*int sensor_select_touch()
{
  

  return select_home;
  
}

int data_log_touch()
{
  if((x >= 201 && x <= 310) && (y >= 80 && y<= 111))
  {
    select_home = 4;
  }
  if((x >= 201 && x <= 310) && (y >= 137 && y<= 168))
  {
    select_home = 5;
  }
  if((x >= 201 && x <= 310) && (y >= 190 && y<= 220))
  {
    select_home = 6;
  }

  return select_home;
}*/
