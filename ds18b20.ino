/*void ds18b20_read()
{
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit;

  if (!ds.search(addr) ) //&& OneWire::crc8(addr, 7) != addr[7]) 
  {
      //tft.fillRect(4,60,313,115,ILI9341_BLACK);
      if(ds18b20_read_display = false)
      {
       tft.fillRect(4,60,313,115,ILI9341_BLACK);
       ds18b20_read_display = true;
      }

      tft.fillRect(6,64,220,35,ILI9341_BLACK);
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(3);
      tft.setCursor(7,65);
      tft.print("Sensor Error");
      ds18b20_reader = false;
      //ds18b20_read_display = true;
      //delay(300);
      ds.reset_search();
      return;
  }
  else
  {
      ds18b20_reader = true;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) 
  {
      Serial.println("CRC is not valid!");
      return;
  }

  Serial.println();
 
  // the first ROM byte indicates which chip
  switch (addr[0]) 
  {
    case 0x10:
      Serial.println("  Chip = DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("  Chip = DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("  Chip = DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");
      return;
  } 
  
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
    
  delay(1000);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.
    
    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad
  
   
    for ( i = 0; i < 9; i++) 
    {           // we need 9 bytes
      data[i] = ds.read();
    }
    // Convert the data to actual temperature
    // because the result is a 16 bit signed integer, it should
    // be stored to an "int16_t" type, which is always 16 bits
    // even when compiled on a 32 bit processor.
    int16_t raw = (data[1] << 8) | data[0];
    if (type_s) 
    {
      raw = raw << 3; // 9 bit resolution default
      if (data[7] == 0x10) 
      {
        // "count remain" gives full 12 bit resolution
        raw = (raw & 0xFFF0) + 12 - data[6];
      }
    } 
    else 
    {
      byte cfg = (data[4] & 0x60);
      // at lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      //// default is 12 bit resolution, 750 ms conversion time
    }
    celsius = (float)raw / 16.0;
    //fahrenheit = celsius * 1.8 + 32.0;
    //Serial.print("  Temperature = ");
  
    liq_temp = celsius;
    
    if(ds18b20_reader == true)
    {
      if(ds18b20_read_display = true)
      {
         tft.fillRect(4,60,313,115,ILI9341_BLACK);
         ds18b20_read_display = false;
      }
         
      //ds18b20_read_display = false;  
      tft.setTextColor(ILI9341_WHITE);
      tft.setTextSize(2);
      tft.setCursor(7,65);
      tft.print("Temperature Reading: ");
      tft.fillRect(99,109,100,33,ILI9341_BLACK);
      tft.setTextColor(ILI9341_GREEN);
      tft.setTextSize(3);
      tft.setCursor(100,110);
      tft.print(liq_temp,2);
      tft.setCursor(70,135);
      tft.setTextSize(2);
      tft.print(" deg Celcius");
    }


 

  /*if(wifi_flag == true && info_screen_flag == false)
  {
     wifi_data_thingsboard();
     liqt_data_thingsboard();
  }*/

  /*if(ble_data_mode_flag == true && info_screen_flag == false)
  {
    if(t.sec != last_second)
    {
     Serial2.print(date_stamp);
     Serial2.print(" ");
     Serial2.print(time_stamp);
     Serial2.print(" Liq Temperature:");
     Serial2.print(liq_temp.float_value);
     Serial2.println(" *C");
     last_second = t.sec;
    }
  }*/

  /*if(sd_card_log_flag == true && info_screen_flag == false)
  {
      t = rtc.getTime();
     if(t.sec >= last_second + 5)
     {
       sd_data = time_stamp + ',' + "Liq _Temp:" + ',' + liq_temp.float_value + ','+ " *C ";
       sd_card_log_data(3);
       last_second = t.sec;
     } 
  }*/
//}

void ds18b20_read()
{
  boolean valid_add = check_address(sensor_add);
  

  if(valid_add == false)
  {
      if(ds18b20_read_display_invalid == false)
      {
       tft.fillRect(4,60,313,115,ILI9341_BLACK);
       ds18b20_read_display_invalid = true;
       ds18b20_read_display_valid = false;
        tft.fillRect(6,64,220,35,ILI9341_BLACK);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(3);
        tft.setCursor(7,65);
        tft.print("Sensor Error");
      }
  }
  else
  {
    if(ds18b20_read_display_valid == false)
    {
         ds18b20_read_display_valid = true;
         ds18b20_read_display_invalid = false;
         tft.fillRect(4,60,313,115,ILI9341_BLACK);
         tft.setTextColor(ILI9341_WHITE);
         tft.setTextSize(2);
         tft.setCursor(7,65);
         tft.print("Temperature Reading: ");
         tft.drawLine(160, 92, 160, 165, ILI9341_YELLOW);
         tft.setTextColor(ILI9341_WHITE);
         tft.setTextSize(1);
         tft.setCursor(10,145);
         tft.print("    deg Celcius");

         tft.setCursor(175,145);
         tft.print("    deg Fahrenheit");
    }
    
    sensors.requestTemperatures(); // Send the command to get temperatures
    
    current_temp = sensors.getTempCByIndex(0);
    
      //ds18b20_read_display = false;  
      if(last_temp != current_temp)
      {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(4);
        tft.fillRect(9,99,124,29,ILI9341_BLACK);
        tft.setCursor(10,100);
        tft.fillRect(194,99,120,29,ILI9341_BLACK);
        tft.print(current_temp,2); 
        tft.setTextColor(ILI9341_CYAN);
        tft.setCursor(182,100);
        tft.print(DallasTemperature::toFahrenheit(current_temp),2);
        last_temp = current_temp;

        if(valid_add == true)
        {

          
             
          if(ble_flag == false && wifi_flag == true)
          {
            wifi_data_thingsboard();
            temp_data_thingsboard();
          }
        
          if(ble_flag == true && wifi_flag == false)
          {
              RTC_data();
             ds_logdata = time_stamp;
             ds_logdata = ds_logdata + ',' + "Temp: " + ',' + current_temp + ',' + " *C";
             Serial2.println(ds_logdata);
          }
        }
      }
      Ds_logdata = "Ds_Temp: ";
      Ds_logdata + Ds_logdata + ',' + current_temp + ','+ "deg Cel";
  }  
}

bool check_address(DeviceAddress deviceaddress)
{
  if(sensors.getAddress(deviceaddress,0))
  {
   // Serial.println("Address_ok");
    return true;
  }
    
  else
  {
    //Serial.println("Invalid Address");
    return false;
  }
}

void getds18b20_add()
{
   int numberOfDevices = sensors.getDeviceCount();
   
   if(sensors.getAddress(tempDeviceAddress, 0))
   { 
    
    // set the resolution to TEMPERATURE_PRECISION bit (Each Dallas/Maxim device is capable of several different resolutions)
    sensors.setResolution(tempDeviceAddress, TEMPERATURE_PRECISION);

    //Serial.println("got address");
    
   }
}

void temp_data_thingsboard()
{
      temp_data = String(current_temp);
      /*hum = String(h);
      tem =  String(tem);
      luxV = String(lux);*/
      
      String payload = "{";
      /*payload += "\"humidity\":"; payload += hum;
      payload += ",";
      payload += "\"amb_temp\":"; payload += tem;
      payload += ",";
      payload += "\"li\":"; payload += luxV;
      payload += ",";*/
      payload += "\"liq_temp\":"; payload += current_temp;
      payload += ",";
      payload += "\"liq_tempf\":"; payload += DallasTemperature::toFahrenheit(current_temp);
      payload += "}";
    
      // Send payload
      char attributes[50];
      payload.toCharArray( attributes, 50 );
      client.publish("v1/devices/me/telemetry", attributes );
      //Serial.println( attributes );
     
  client.loop();
  return;
}
     
