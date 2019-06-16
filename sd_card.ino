
void sdcard_screen_mandate()
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
  tft.print("   SD Card Configuration");

  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  
  tft.fillRect(10,185,97,45,ILI9341_LIGHTGREY);
  tft.setCursor(20,200);
  tft.print("Refresh");
  
  tft.fillRect(215,185,98,45,ILI9341_LIGHTGREY);
  tft.setCursor(240,200);
  tft.print("HOME");
}

void card_info()
{
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  sdcard_noti_flag = true;

  bool card_init = false;
  //delay(20);
  if(!card.init(SPI_HALF_SPEED, chipSelect)) 
  { 
    card_init = false;
    sdcard_flag = false;
  }
  else
  {
     card_init = true;
  }
  
   
  if(card_init == false)
  {
    tft.setCursor(20,68);
    tft.print("No Card Found or");
    tft.setCursor(20,98);
    tft.print("Currupted Card");
  }
  else
  {
    sd_card_details();
  }

  if(sdcard_noti_flag == true)
  {
    notification();
    sdcard_noti_flag = false;
  }
}

/*bool sd_card_init()
{
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);

  //cardOn();
  
  if(!card.init(SPI_HALF_SPEED, chipSelect)) 
  {
    return false;
    Serial.println("CArd not Found");
  }
  else
  {
    return true;
    Serial.println("CArd OK");
  }
  
    
}*/


void sd_card_details()
{
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(5,60);
  tft.print("Card Type: ");

  ///cardOn();
  
  //screenOn();
  switch (card.type()) 
  {
    case SD_CARD_TYPE_SD1:
                          tft.print("SD1");
                          Serial.println("SD1");
                          break;
                          
    case SD_CARD_TYPE_SD2:tft.print("SD2");
                          Serial.println("SD2");
                          break;
                          
    case SD_CARD_TYPE_SDHC:tft.print("SDHC");
                           Serial.println("SDHC");
                           break;
      
    default:tft.print("UNKNOWN");
            Serial.println("UNKNOWN");
            break;
  }
  
  //cardOn();

  int volume_init = 1;
  if (!volume.init(card))
  {
    volume_init = 0; 
  }

  //screenOn();
  tft.setCursor(5,90);
  sdcard_noti_flag = true;
  if(volume_init == 0)
  {
    sdcard_flag = false;
    tft.print("Format Card in FAT32");
    Serial.println("Format Card");
  }
  else
  {
    //cardOn();
    sdcard_flag = true;
    
    uint32_t volumesize;
    volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
    volumesize *= volume.clusterCount();       // we'll have a lot of clusters
    volumesize /= 2;  
    volumesize /= 1024;

   // screenOn();
    
    tft.print("Volume type: FAT32 ");
    Serial.println("Volume type: FAT32");
    //tft.print(volume.fatType());
    
    tft.setCursor(5,120);
    tft.print("Volume Size: ");
    Serial.println("Volume Size: ");
    
    
    tft.print((float)volumesize / 1024.0,2);
    tft.print (" GB");
    Serial.println("GB");
  }
}

void sdcardcheck_inloop()
{
  if(!card.init(SPI_HALF_SPEED, chipSelect)) 
  { 
    sdcard_flag = false;
    //sdcard_noti_flag = false;
  }
  else
  {
     sdcard_flag = true;
     sdcard_noti_flag = true;
  }

  if(sdcard_flag == true)
  {
    int volume_init = 1;
    if (!volume.init(card))
    {
      volume_init = 0; 
    }
    
    if(volume_init == 0)
    {
      sdcard_flag = false;
      //sdcard_noti_flag = false;
    }
    else
    {
      sdcard_flag = true; 
      sdcard_noti_flag = true;
    }
  }
  
}

void create_open_file(int sensor_id, String sensor_logdata)
{
  RTC_data();
  
  file_name = date_stamp + ".csv";

  time_stamplog = time_stamp;

  switch(sensor_id)
  {
    case 1: file_name = "pH_" + file_name;
            break;
    case 2: file_name = "DS_" + file_name;
            time_stamplog = time_stamplog + ',' + "Temp: " + ',' + current_temp + ',' + " *C";
            break;
    case 3: file_name = "Tur_" + file_name;
            break;
  }

  Serial.println(file_name);
  Serial.println("opening file");

  if (!SD.begin(SPI_HALF_SPEED, chipSelect)) 
  {
    Serial.println("initialization failed!");
    //return;
  }
  
  myFile = SD.open("file_name", FILE_WRITE);

  if (myFile) 
  {
     myFile.println(time_stamplog);
     myFile.close();
     Serial.println("done.");
  }
}
