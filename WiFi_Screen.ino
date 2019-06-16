


void wifi_screen_mandate()
{
  tft.fillScreen(ILI9341_BLACK);

  tft.drawRect(0,0,320,240,ILI9341_PURPLE);
  tft.drawRect(2,2,251,25,ILI9341_WHITE);
  tft.drawRect(254,2,64,25,ILI9341_YELLOW);
  tft.drawRect(2,28,316,25,ILI9341_CYAN);
  
  tft.drawRect(2,57,316,123,ILI9341_GREEN);

  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(7,33);
  tft.print("WiFi Configuration Screen");

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  
  tft.setCursor(35,190);
  tft.print("WiFi");
  tft.setCursor(22,210);
  tft.print("ON/OFF");
  
  tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
  tft.setCursor(140,190);
  tft.print("New");
  tft.setCursor(120,210);
  tft.print("Network");

  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,200);
  tft.print("HOME");
}

void wifi_screen()
{
  if(wifi_screen_flag == false)
  {
   wifi_screen_mandate();
   wifi_screen_flag = true;
  }
  
  tdn_window();
  
  if(wifi_noti_flag == true)
  {
    notification();
    wifi_noti_flag = false;
  }

  if(wifi_connect_flag == false)
  {
    
    
    if(wifi_flag == false)
    { 
      tft.fillRect(4,60,313,115,ILI9341_BLACK); 
      tft.setTextColor(ILI9341_LIGHTGREY);
      tft.setTextSize(2);
     tft.setCursor(50,68);
     tft.print(" First Turn On WiFi");
    }
    else
    {
      
      WIFI_AP = WiFi.SSID(wifi_network_no);
      
      while (status != WL_CONNECTED) 
      {
       
        Serial.println(WIFI_AP);
        // Connect to WPA/WPA2 network
        //status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
        status = WiFi.beginOn(WIFI_AP);
        delay(200);
      }
      
      tft.fillRect(4,60,313,115,ILI9341_BLACK); 
      tft.setTextColor(ILI9341_LIGHTGREY);
      tft.setTextSize(2);
      
      tft.setCursor(10, 68);
      tft.print("MAC: ");
      //tft.print("80:12:14:56:F5");
      printMacAddress();
  
      tft.setCursor(10, 98);
      tft.print("SSID: ");
      //tft.print("Hypatia_MBFF_119-x142");
      tft.print(WiFi.SSID(wifi_network_no));
  
      tft.setCursor(10,150);
      tft.print("IP: ");
      IPAddress ip = WiFi.localIP();
      tft.print(ip);
      
    }
    wifi_connect_flag = true;
  }
  
}

void listnetwork_table()
{
  tft.fillRect(5,60,310,25,ILI9341_LIGHTGREY);
  tft.fillRect(5,90,310,25,ILI9341_LIGHTGREY);
  tft.fillRect(5,120,310,25,ILI9341_LIGHTGREY);
  tft.fillRect(5,150,310,25,ILI9341_LIGHTGREY);
}
