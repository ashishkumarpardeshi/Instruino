void pH_screen_mandate()
{
  tft.fillScreen(ILI9341_BLACK);

  tft.drawRect(0,0,320,240,ILI9341_PURPLE);
  tft.drawRect(2,2,251,25,ILI9341_WHITE);
  tft.drawRect(254,2,64,25,ILI9341_YELLOW);
  tft.drawRect(2,28,316,25,ILI9341_CYAN);
  
  tft.drawRect(2,57,316,123,ILI9341_GREEN);

  /*tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(7,33);
  tft.print("  pH Sensor Measurement");*/

  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(3);
      
  tft.setCursor(7,70);
  tft.print("pH: ");

  //tft.setCursor(140,70);
  //tft.print("T= ");

  tft.setCursor(7,110);
  tft.print("Temp: ");

  
  tft.setTextSize(2);
  tft.setCursor(7,150);
  tft.print("Voltage: ");
  tft.setCursor(220,150);
  tft.print("CB: ");

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  
  tft.setCursor(35,190);
  tft.print("Data");
  tft.setCursor(22,210);
  tft.print("Logging");
  
  tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
  tft.setCursor(115,190);
  tft.print("pH Probe");
  tft.setCursor(146,210);
  tft.print("CAL");

  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,200);
  tft.print("HOME");
}

void pH_calibration_window()
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
  tft.print("  pH Calibration Unit");

  /*tft.setTextColor(ILI9341_GREEN);
  tft.setCursor(7,33);
  tft.print("pH Calibration Unit");*/
  

 /* tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  
  tft.setCursor(35,200);
  tft.print(" OK");
  
  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,190);
  tft.print(" pH ");
  tft.setCursor(240,210);
  tft.print("HOME");*/

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  tft.setCursor(35,190);
  tft.print(" CAL");
  tft.setCursor(35,210);
  tft.print("4.01");
  
  tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
  tft.setCursor(139,190);
  tft.print(" CAL");
  tft.setCursor(139,210);
  tft.print("7.00");
    
  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,190);
  tft.print(" CAL");
  tft.setCursor(240,210);
  tft.print("9.18");

  tft.fillRect(215,130,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,145);
  tft.print(" OK");
}

void pH_calibration()
{
  pH_calibration_window();
  notification();

  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
      
  tft.setCursor(7,70);
  tft.print("pH = ");

  tft.setCursor(140,70);
  tft.print("T= ");

  tft.setCursor(7,110);
  tft.print("Voltage = ");

  tft.setCursor(220,110);
  tft.print("CB: ");

  tft.setCursor(7,150);
  tft.print("Offset = ");

  ph_screen_flag = false;  
  last_day = 0;
  last_date_stamp = "00";
}

void pH_cal_buffer_select()
{
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  
   if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220))
   {
      tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
      tft.setCursor(240,190);
      tft.print(" CAL");
      tft.setCursor(240,210);
      tft.print("9.18");

      tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
      tft.setCursor(139,190);
      tft.print(" CAL");
      tft.setCursor(139,210);
      tft.print("7.00");

      tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
      tft.setCursor(35,190);
      tft.print(" CAL");
      tft.setCursor(35,210);
      tft.print("4.01");
      
      cal_buffer = 9.18;
   }

   if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220))
   {
      tft.fillRect(10,185,97,45,ILI9341_GREEN);
      tft.setCursor(35,190);
      tft.print(" CAL");
      tft.setCursor(35,210);
      tft.print("4.01");

      
      tft.fillRect(215, 185, 98, 45, ILI9341_LIGHTGREY);
      tft.setCursor(240,190);
      tft.print(" CAL");
      tft.setCursor(240,210);
      tft.print("9.18");

      tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
      tft.setCursor(139,190);
      tft.print(" CAL");
      tft.setCursor(139,210);
      tft.print("7.00");

      
      cal_buffer = 4.01;
   }

   if ((x >= 130 && x <= 204) && (y >= 190 && y <= 220))
   {
      tft.fillRect(114,185,94,45,ILI9341_GREEN);
      tft.setCursor(139,190);
      tft.print(" CAL");
      tft.setCursor(139,210);
      tft.print("7.00");

      tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
      tft.setCursor(35,190);
      tft.print(" CAL");
      tft.setCursor(35,210);
      tft.print("4.01");

      
      tft.fillRect(215, 185, 98, 45, ILI9341_LIGHTGREY);
      tft.setCursor(240,190);
      tft.print(" CAL");
      tft.setCursor(240,210);
      tft.print("9.18");

      cal_buffer = 7.00;
   }

   if ((x >= 220 && x <= 300) && (y >= 132 && y <= 170))
   {
      tft.fillRect(215,130,98,45,ILI9341_GREEN);
      tft.setCursor(240,145);
      tft.print(" OK");
          
      tft.fillRect(215,130,98,45,ILI9341_LIGHTGREY);
      tft.setCursor(240,145);
      tft.print(" OK");
      last_date_stamp = -1;
      last_pH = -1;
      last_temp =  -1;
      last_cal_buffer = -1;
      last_voltage = -1;
      ok = true;
      ph_cal_flag = false;
      last_day = -1;
    }
}

void pH_read()
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  
  current_temp = 0.00, last_temp = 0.00; 
  temp_err = false;
  
  boolean valid_add = check_address(sensor_add);
  
  if(valid_add == false)
  {
    temp_err = false;
  }
  else
  {
    temp_err = true;
    sensors.requestTemperatures(); // Send the command to get temperatures
    current_temp = sensors.getTempCByIndex(0);
  }

  if(millis()- samplingTime > samplingInterval)
  {
      //Serial.println("if miilis 1");
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      
      if(ph_cal_flag == true)
        pHValue = 3.5*voltage;
        else
        pHValue = 3.5*voltage + Offset;
        
      samplingTime=millis();
  }

  
  
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    //Serial.println("if miilis 2");
    if(ph_cal_flag == true)
    { 
      Offset = cal_buffer - pHValue;
      //Serial.println("if ph_cal_flag true");
      
      if(pHValue != last_pH)
      {
        tft.fillRect(65,70,50,20,ILI9341_BLACK);
        tft.setCursor(65,70);
        tft.print(pHValue,2);
        last_pH = pHValue;
      }
        
      if(temp_err == true)
      {
        if(current_temp != last_temp)
        {
          tft.fillRect(175,70,110,20,ILI9341_BLACK);
          tft.setCursor(175,70);
          tft.print(current_temp,2);
          tft.print(" degC");
          last_temp = current_temp;
        }
      }
      else
      {
        tft.setCursor(175,70);
        tft.print("Error");
      }

      if(voltage != last_voltage)
      {
        tft.fillRect(130,110,87,20,ILI9341_BLACK);
        tft.setCursor(130,110);
        tft.print(voltage,2);
        last_voltage = voltage;
        tft.print("mV");
      }

      if(cal_buffer != last_cal_buffer)
      {
        tft.fillRect(260,110,50,20,ILI9341_BLACK);
        tft.setCursor(260,110);
        if(cal_buffer == 4.01 || cal_buffer == 7.00 || cal_buffer == 9.18)
        {
          tft.print(cal_buffer,2);
        }
        else
        {
          tft.print("NS");
        }
        last_cal_buffer = cal_buffer;
      }
      
      if(Offset != last_offset)
      {
        tft.fillRect(120,150,60,20,ILI9341_BLACK);
        tft.setCursor(120,150);
        if(cal_buffer == 4.01 || cal_buffer == 7.00 || cal_buffer == 9.18)
        {
          tft.print(Offset,2);
        }
        else
        {
          tft.print("NA");
        }
        last_offset = Offset;
      }
    }
    
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(3);
    
    if(pHValue != last_pH)
    {
      tft.fillRect(60,70,100,30,ILI9341_BLACK);
      tft.setCursor(60,70);
      tft.print(pHValue,2);
      last_pH = pHValue;
      
      if(wifi_flag == true && ble_flag == false)
      {
        wifi_data_thingsboard();

        ph_data_thingsboard();
      }

      if(ble_flag == true && wifi_flag == false)
      {
          RTC_data();
          ph_logdata = time_stamp;
          ph_logdata = ph_logdata + ',' + "Voltage: ";
          ph_logdata = ph_logdata + ',' + voltage + ',' + " V"+ ',' + "pH: " + ',' + pHValue + ',' + "Temp: " + ',' + current_temp + ',' + " *C";

          Serial2.println(ph_logdata);
      }
      
    }

    if(temp_err == true)
    {
      if(current_temp != last_temp)
      {
        tft.fillRect(110,110,160,30,ILI9341_BLACK);
        tft.setCursor(110,110);
        tft.print(current_temp,2);
        tft.print(" *C");
        last_temp = current_temp;
      }
    }
    else
    {
       tft.setCursor(130,110);
       tft.print("Error");
    }

   tft.setTextColor(ILI9341_WHITE);
   tft.setTextSize(2);
   
   if(voltage != last_voltage)
   {
        tft.fillRect(110,150,70,20,ILI9341_BLACK);
        tft.setCursor(110,150);
        tft.print(voltage,2);
        last_voltage = voltage;
        tft.print("mV");
    }

    if(cal_buffer != last_cal_buffer)
    {
      tft.fillRect(260,150,50,20,ILI9341_BLACK);
      tft.setCursor(260,150);
      if(cal_buffer == 4.01 || cal_buffer == 7.00 || cal_buffer == 9.18)
      {
        tft.print(cal_buffer,2);
      }
      else
      {
        tft.print("NS");
      }
      last_cal_buffer = cal_buffer;
    }
    
    Serial.print("Voltage:");
    Serial.print(voltage,2);
    Serial.print("    pH value: ");
    Serial.println(pHValue,2);
    printTime=millis();
  }
}

double avergearray(int* arr, int number)
{
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}



void ph_data_thingsboard()
{
      ph_data = String(pHValue);
      /*hum = String(h);
      tem =  String(tem);
      luxV = String(lux);*/
      
      String payload = "{";
      /*payload += "\"humi\":"; payload += hum;
      payload += ",";
      payload += "\"ambt\":"; payload += tem;
      payload += ",";
      payload += "\"li\":"; payload += luxV;
      payload += ",";*/
      payload += "\"ph\":"; payload += ph_data; payload += ",";
      payload += "\"volt\":"; payload += voltage;
      
      if(temp_err == true)
      {
        payload += ",";
        payload += "\"liqt\":"; payload += current_temp;
      }
      
      payload += "}";
    
      // Send payload
      char attributes[100];
      payload.toCharArray( attributes, 100 );
      client.publish("v1/devices/me/telemetry", attributes );
      //Serial.println( attributes );
     
  client.loop();
  return;
}

void sensorhtl_data_thingsboard()
{
      hum = String(h);
      tem =  String(tem);
      luxV = String(lux);
      
      String payload = "{";
      payload += "\"humi\":"; payload += hum;
      payload += ",";
      payload += "\"ambt\":"; payload += tem;
      payload += ",";
      payload += "\"li\":"; payload += luxV;
      payload += "}";
    
      // Send payload
      char attributes[200];
      payload.toCharArray( attributes, 200 );
      client.publish("v1/devices/me/telemetry", attributes );
      //Serial.println( attributes );
     
  client.loop();
  return;
}
     
