void turbidity_screen_mandate()
{
  tft.fillScreen(ILI9341_BLACK);

  tft.drawRect(0,0,320,240,ILI9341_PURPLE);
  tft.drawRect(2,2,251,25,ILI9341_WHITE);
  tft.drawRect(254,2,64,25,ILI9341_YELLOW);
  tft.drawRect(2,28,316,25,ILI9341_CYAN);
  
  tft.drawRect(2,57,316,123,ILI9341_GREEN);

  /* tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(2);
  tft.setCursor(7,33);
  tft.print("  Turbidity Measurements");*/

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);

  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  
  tft.setCursor(35,190);
  tft.print("Data");
  tft.setCursor(22,210);
  tft.print("Logging");
  
  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,200);
  tft.print("HOME");
}

void turbidity_read()
{
  if(turbidity_read_display == false)
    {
         turbidity_read_display = true;
         tft.fillRect(4,60,313,115,ILI9341_BLACK);
         tft.setTextColor(ILI9341_WHITE);
         tft.setTextSize(2);
         tft.setCursor(7,65);
         tft.print("Turbidity Measurement: ");
         tft.drawLine(160, 92, 160, 165, ILI9341_YELLOW);
         tft.setTextColor(ILI9341_WHITE);
         tft.setTextSize(2);
         tft.setCursor(10,145);
         tft.print("  Volts");

         tft.setCursor(195,145);
         tft.print("  NTU");
    }
    volt = 0.00;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(turbidityPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,1);
    if(volt < 2.5)
    {
      ntu = 3000;
    }else
    {
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8; 
    }

    if(last_volt_turbidity != volt)
    {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(3);
        tft.fillRect(29,99,124,29,ILI9341_BLACK);
        tft.setCursor(30,100);
        tft.fillRect(179,99,130,29,ILI9341_BLACK);
        tft.print(volt,2); 
        tft.setTextColor(ILI9341_CYAN);
        tft.setCursor(180,100);
        tft.print(ntu,2);
        last_volt_turbidity = volt;

        if(ble_flag == false && wifi_flag == true)
        {
          wifi_data_thingsboard();
          turbidity_data_thingsboard();
        }

        if(ble_flag == true && wifi_flag == false)
        {
          RTC_data();
          turbidity_logdata = time_stamp;
          turbidity_logdata = turbidity_logdata + ',' + "Voltage: ";
          turbidity_logdata = turbidity_logdata + ',' + volt + ',' + " V" + ',' + "Turbidity: " + ',' + ntu + ',' + " NTU";

          Serial2.println(turbidity_logdata);
        }
        
     }
     
    
    delay(10);
}

float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}

void turbidity_data_thingsboard()
{
      turbidity_data = String(ntu);
      volt_tur = String(volt);
     /* hum = String(h);
      tem =  String(tem);
      luxV = String(lux);*/
      
      String payload = "{";
      /*payload += "\"humidity\":"; payload += hum;
      payload += ",";
      payload += "\"amb_temp\":"; payload += tem;
      payload += ",";
      payload += "\"li\":"; payload += luxV;
      payload += ",";*/
      payload += "\"turbidity\":"; payload += turbidity_data;
      payload += ",";
      payload += "\"tur_volt\":"; payload += volt_tur;
      payload += "}";
    
      // Send payload
      char attributes[50];
      payload.toCharArray( attributes, 50 );
      client.publish("v1/devices/me/telemetry", attributes );
      //Serial.println( attributes );
     
  client.loop();
  return;
}
