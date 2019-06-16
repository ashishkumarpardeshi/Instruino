
void ble_screen_mandate()
{
  tft.fillScreen(ILI9341_BLACK);

  tft.drawRect(0,0,320,240,ILI9341_PURPLE);
  tft.drawRect(2,2,251,25,ILI9341_WHITE);
  tft.drawRect(254,2,64,25,ILI9341_YELLOW);
  tft.drawRect(2,28,316,25,ILI9341_CYAN);
  
  tft.drawRect(2,57,316,123,ILI9341_GREEN);

   tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(14,33);
  tft.print(" Bluetooth Configuration");

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  
  tft.setCursor(12,190);
  tft.print("Bluetooth");
  tft.setCursor(20,210);
  tft.print("ON/OFF");
  
  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,200);
  tft.print("HOME");
}

void ble_screen()
{
  if(ble_screen_flag == false)
  {
   ble_screen_mandate();
   ble_screen_flag = true;
  }
  
  tdn_window();
  
  if(ble_noti_flag == true)
  {
    notification();
    ble_noti_flag = false;
  }

  if(ble_connect_flag == false)
  {
    tft.fillRect(4,60,313,115,ILI9341_BLACK); 
    tft.setTextColor(ILI9341_LIGHTGREY);
    tft.setTextSize(2);
    
    if(ble_flag == false)
    { 
     tft.setCursor(14,68);
     tft.print("First Turn ON Bluetooth");
    }
    else
    {
     tft.setCursor(14,68);
     tft.print("Bluetooth Name: Instruino");
     tft.setCursor(14,98);
     tft.print("  Bluetooth Turned ON");
     tft.setCursor(14,128);
     tft.print("You can Pair to view Data");
    }
    ble_connect_flag = true;
  }
  
}
