

void home_screen()
{
  tft.fillScreen(ILI9341_BLACK);
  //tft.background(0,0,0);
  delay(1);
  
  tft.drawRect(0,0,320,240,ILI9341_PURPLE);
  tft.drawRect(2,2,251,25,ILI9341_WHITE);
  tft.drawRect(254,2,64,25,ILI9341_YELLOW);
  tft.drawRect(2,28,316,25,ILI9341_CYAN);
  tft.drawRect(5,70,176,167,ILI9341_GREEN);
  tft.drawRect(187,70,129,167,ILI9341_WHITE);

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  
  tft.fillRect(10,75,165,45,ILI9341_ORANGE);
  tft.setCursor(45,90);
  tft.print("pH Probe");
  
  tft.fillRect(10,130,165,45,ILI9341_PINK);
  tft.setCursor(33,145);
  tft.print("Temp Probe");
  
  tft.fillRect(10,185,165,45,ILI9341_BLUE);
  tft.setCursor(40,200);
  tft.print("Turbidity");

  tft.fillRect(192,75,120,45,ILI9341_WHITE);
  tft.setCursor(233,90);
  tft.print("WiFi");
  tft.fillRect(192,130,120,45,ILI9341_WHITE);
  tft.setCursor(198,145);
  tft.print("Bluetooth");
  tft.fillRect(192,185,120,45,ILI9341_WHITE);
  tft.setCursor(211,200);
  tft.print("SD Card");

  //------------------------------Sensors and Data Comm LAbel-------------------------------------
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(1);
    
    tft.setCursor(75,59);
    tft.print("Sensors");
  
    tft.setCursor(193,59);
    tft.print("Measurements Logging");
  //----------------------------------------------------------------------------------------------

  
}

void notification()
{
  tft.setTextSize(2);
  //----------------- Wifi, BLE and SD Card Status window ---------------------------------
  
  tft.setCursor(258, 7);
  if(wifi_flag == false)
  {
    tft.setTextColor(ILI9341_RED);
  }
  else
  {
    tft.setTextColor(ILI9341_GREEN);
  }
  tft.print("W ");

  tft.setCursor(281, 7);
  if(ble_flag == false)
  {
    tft.setTextColor(ILI9341_RED);
  }
  else
  {
    tft.setTextColor(ILI9341_GREEN);
  }
  tft.print("B ");

  tft.setCursor(303, 7);
  if(sdcard_flag == false)
  {
    tft.setTextColor(ILI9341_RED);
  }
  else
  {
    tft.setTextColor(ILI9341_GREEN);
  }
  tft.print('S');
  //----------------------------------------------------------------------------------------------
}

void tdn_window()
{
  
   tft.setTextSize(2);
  //--------------------------------- Time Date Stamp window -------------------------------------
  
  tft.setTextColor(ILI9341_WHITE);
  
  RTC_data();
  
  if(t.dow != last_day)
  {
    tft.setCursor(5, 6);
    last_day = t.dow;
    //Serial.print("last Day: ");
    //Serial.println(last_day);
    tft.fillRect(5,5,22,18,ILI9341_BLACK);
    tft.print(days[last_day]);
    tft.print(" ");
  }
  
  if(date_stamp != last_date_stamp)
  {
    tft.setCursor(50, 6);
    last_date_stamp = date_stamp;
    tft.fillRect(48,5,105,18,ILI9341_BLACK);
    tft.print(date_stamp);
    tft.print(" ");
  }
  if(time_stamp != last_time_stamp)
  {
    tft.setCursor(153, 6);
    last_time_stamp = time_stamp;
    
    if(t.sec != lastsec)
    {
      lastsec = t.sec;
      tft.fillRect(225,5,26,18,ILI9341_BLACK);
    }
    if(t.min != lastmin)
    {
      lastmin = t.min;
      tft.fillRect(185,5,30,18,ILI9341_BLACK);
    }
    if(t.hour != lasthour)
    {
      lasthour = t.hour;
      tft.fillRect(145,5,30,18,ILI9341_BLACK);
    }
    //tft.fillRect(151,5,105,18,ILI9341_BLACK);
    tft.print(time_stamp);
  }
  //----------------------------------------------------------------------------------------------

}

void htl_window()
{
   //-------------------------- Humidity Temperature and Light Instensity Window ------------------
  
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(1);

  h = dht.readHumidity();
  T = dht.readTemperature();

  lux = lightMeter.readLightLevel();

  
  tft.setCursor(7,37);
  tft.print("Hu:");
  tft.setCursor(25,33);
  tft.setTextSize(2);
  if(h != lasthum)
  {
    lasthum = h;
    tft.fillRect(24,33,62,18,ILI9341_BLACK);
    tft.print(h,2);
  }
  tft.setCursor(88,40);
  tft.setTextSize(1);
  tft.print("%");

  tft.setTextSize(1);

  tft.setCursor(103,37);
  tft.print("Te:");
  tft.setCursor(126,33);
  tft.setTextSize(2);
  if(T != lasttemp)
  {
    lasttemp = T;
    tft.fillRect(125,33,65,18,ILI9341_BLACK);
    tft.print(T,2);
  }
  tft.setCursor(188,37);
  tft.setTextSize(1);
  tft.print("o");
  tft.setCursor(195,40);
  tft.print("C");

  
  tft.setTextSize(1);
  tft.setCursor(210,37);
  tft.print("LI:");
  tft.setCursor(231,33);
  tft.setTextSize(2);
  if(lux != lastlux)
  {
    lastlux = lux;
    tft.fillRect(230,33,131,18,ILI9341_BLACK);
    tft.print(lux);
  }
  tft.setCursor(303,40);
  tft.setTextSize(1);
  tft.print("Lx");
  //----------------------------------------------------------------------------------------------
}

void imp_flag()
{
  home_flag = false;
  last_day = -1;
  last_date_stamp = -1;
  lasttemp = -1;
  lasthum = -1;
  lastlux = -1;
}
