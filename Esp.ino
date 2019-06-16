
void InitWiFi()
{
  // initialize serial for ESP module
  Serial3.begin(115200);
  // initialize ESP module
  WiFi.init(&Serial3);
  // check for the presence of the shield
  
  if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("WiFi absent");
    // don't continue
    //while (true);
  }
  else
  {
    Serial.println("WiFi found");
    //printMacAddress();
  }
  //delay(100);  
  //Ap_connection();
}

/*void Ap_connection()
{
  listNetworks();
  delay(20);
  //lap_up_down();
  //WIFI_AP = WiFi.SSID(lap[nav]);

  //lcd.clear();
 // lcd.setCursor(0,0);
 // lcd.print("M: ");
  printMacAddress();
 // lcd.setCursor(0,1);
 // lcd.print("SSID: ");
  //lcd.print(WIFI_AP);
  
  
  //Serial.println("Conn to AP ...");
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) 
  {
   // lcd.setCursor(0,2);
    //lcd.print("Connecting");
    //Serial.print("Attemp to connect SSID: ");
    Serial.println(WIFI_AP);
    
    // Connect to WPA/WPA2 network
    //status = WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    status = WiFi.beginOn(WIFI_AP);
    delay(500);
  }
  //Serial.println("Connected AP");
  //lcd.setCursor(0,2);
  //lcd.print("Connected       ");
  //lcd.print(WIFI_AP);
  
 // lcd.setCursor(0,3);
  //lcd.print("Obtaining IP");
  delay(1000);
  //lcd.setCursor(0,3);
  //lcd.print("IP: ");
  IPAddress ip = WiFi.localIP();
  //Serial.print("IP Address: ");
  //Serial.println(ip);
  //lcd.print(ip);
  delay(4000);
  //nav = 0;
  //nav_sensors = 0;
}*/

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Connect to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
   /* if(test_data_flag == true)
    {
      #define TOKEN "Instruino_test"
    }
    else
    {
      #define TOKEN "Instruino_Platform"
    }*/

    if ( client.connect("Arduino Uno Device", TOKEN, NULL) ) 
    {
      Serial.println( "[DONE]" );
    } 
    else 
    {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retry in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}

void wifi_data_thingsboard() 
{
  status = WiFi.status();
  if ( status != WL_CONNECTED) 
  {
    while ( status != WL_CONNECTED) 
    {
      Serial.print("connecting to SSID: ");
      Serial.println(WIFI_AP);
      // Connect to WPA/WPA2 network
     //status = WiFi.beginAP(WIFI_AP,WIFI_PASSWORD);
     status = WiFi.beginOn(WIFI_AP);
      delay(500);
    }
   // Serial.println("Got AP");
  }

  if ( !client.connected() ) 
  {
    reconnect();
  }

  return;
}




void printMacAddress()
{
  // get your MAC address
  byte mac[6];
  WiFi.macAddress(mac);
  
  // print MAC address
  char buf[20];
  sprintf(buf, "%02X:%02X:%02X:%02X:%02X:%02X", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
  tft.print(buf);
}


/*void wifi_status()
{
  //lcd.setCursor(0,0);
  if (WiFi.status() == WL_NO_SHIELD) 
  {
   // lcd.setCursor(0,1);
   // lcd.print("   WiFi H/W Error");
   // lcd.setCursor(0,2);
    //lcd.print(" Reset or check ESP");
  }
  else
  {
    if(status == WL_CONNECTED) 
    {
      //lcd.print("M: ");
      printMacAddress();

      //lcd.setCursor(0,1);
      //lcd.print("SSID: ");
      //lcd.print(WIFI_AP);
      
      //lcd.setCursor(0,2);
      //lcd.print("IP: ");
      IPAddress ip = WiFi.localIP();
      //lcd.print(ip);
    }
    else
    {
     // lcd.print("Not Connected");
      //Ap_connection();
    }
  }  
}*/

void listNetworks()
{
  // scan for nearby networks
  int numSsid = WiFi.scanNetworks();
  Serial.println(numSsid);
  unsigned char sn = 0,thisNet;
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);
  for (thisNet = 0; thisNet < numSsid; thisNet++) 
  {
    if(WiFi.encryptionType(thisNet) == ENC_TYPE_NONE && sn <= 3)
    {
      wifi_network_array[sn] = thisNet;
      if(sn == 0)
      {
        tft.fillRect(5,60,310,25,ILI9341_LIGHTGREY);  
        tft.setCursor(10,68);
        tft.print("1:");
        tft.print(WiFi.SSID(thisNet));
      }

      if(sn == 1)
      {
        tft.fillRect(5,90,310,25,ILI9341_LIGHTGREY); 
        tft.setCursor(10,98);
        tft.print("2:");
        tft.print(WiFi.SSID(thisNet));
      }

      if(sn == 2)
      {
        tft.fillRect(5,120,310,25,ILI9341_LIGHTGREY);  
        tft.setCursor(10,128);
        tft.print("3:");
        tft.print(WiFi.SSID(thisNet));
      }

      if(sn == 3)
      {
        tft.fillRect(5,150,310,25,ILI9341_LIGHTGREY);
        tft.setCursor(10,158);
        tft.print("4:");
        tft.print(WiFi.SSID(thisNet));
      }
      sn++;
    }
  }

  while(wifi_network_no == -1)
  {
    touch_read();
    if((x >= 10 && x <= 310) && (y >= 64 && y<= 83))
    {
      wifi_network_no = wifi_network_array[0];
      break;
    }

    if((x >= 10 && x <= 310) && (y >= 96 && y<= 110))
    {
      wifi_network_no = wifi_network_array[1];
      break;
    }

    if((x >= 10 && x <= 310) && (y >= 125 && y<= 140))
    {
      wifi_network_no = wifi_network_array[2];
      break;
    }

    if((x >= 10 && x <= 310) && (y >= 155 && y<= 170))
    {
      wifi_network_no = wifi_network_array[3];
      break;
    }
  }
}
