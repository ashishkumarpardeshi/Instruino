void tempprobe_screen_mandate()
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
  tft.print("  Temp Probe Measurement");*/

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
