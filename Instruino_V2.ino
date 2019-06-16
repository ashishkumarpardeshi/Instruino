/**********************************************************************************************
  Sketch Name: Instruino_v2
  Date: 08-04-2019

  Board Used: Arduino Mega
  IDE used: Arduino 1.8.5

  Coder: Ashish Kumar Pardeshi
  Deisgnation: Project Scientific Officer - B
  Organization: HBCSE, TIFR, Mumbai.

  Description: This Sketch is for a "Instruino" A Common Instrument
             Hardware Platform for measuring the parameters
             (pH, Humidity, Temperature, Turbidity and Light).

  Interfacings:
  S.no    Module        Interface                     Used For
  ----------------- Sensors ------------------------------------------------------
  1       BH1750        I2C (SDA, SCL)                Lux Calculation
  2       DHT22         Dig 2 (1-wire)                Humidity & Temperature
  3       DS18B20       Dig 3 (1-wire)                Liquid Temperature
  4       pH Sensor     Analog A0                     pH Value
  5       Turbidity     Analog A1                     Turbidity of Liquid

  ----------------- Communications & Logging -------------------------------------
  1       Wi-Fi         Serial 3 (Tx3, Rx3)           Things Board
                      WiFi Sw - 30                  WiFi ON OFF Ctrl
  2       Bluetooth     Serial 2 (Tx2, Rx2)           Mobile App Interface
                      Ble Sw  - 25                  Ble ON OFF Ctrl
  3       SD Card       SPI (MISO, MOSI, SCK SS)      Time and Date
  4       Prog/Debug    Serial 0 (Tx0, Rx0)           Programming and Debugging

  ----------------- Display, RTC & Threshold -------------------------------------
  1       2.8" TFT      DC  CS  RST  MISO  MOSI  CLK  TFT Color Screen
                      48  53   49   50    51    52

        Touch Panel   t_SCK t_CS  t_MOSI  t_MISO  t_IRQ
                       22    23     24      25      26

  2       DS3231 RTC    I2C (SDA, SCL)                Date and Time Stamp
  3       Buzzer        Dig 4                         Threshold Audio Alarm
  4       Thres_Led     Dig 5                         Threshold Visual Alarm

  ----------------- Status Led ----------------------------------------------------
  1       Error_Led     Dig 22                        Error Indication
  2       Ok_Led        Dig 23                        Ok Indication
  3       Process_Led   Dig 24                        Processing Indication
**************************************************************************************************/



#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "URTouch.h"

#include <OneWire.h>
#include <DallasTemperature.h>


// WiFi ESP-01
#include <WiFiEspClient.h>
#include <WiFiEsp.h>
#include <WiFiEspUdp.h>
#include <PubSubClient.h>

#include <DS3231.h>

#include <Wire.h>
#include <BH1750.h>
#include "DHT.h"

// SD Card Lib Header
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
#define TEMPERATURE_PRECISION 12 // Higher resolution

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address


uint8_t sensor_add[8] = { 0x28, 0xFF, 0xEE, 0x86, 0x64, 0x16, 0x03, 0x93 };
float last_temp = 0.00, current_temp = 0.00;

float h=0.00;
float T, lux;

String hum, tem, luxV;

// SD Card
const int chipSelect = 10;

Sd2Card card;
SdFile root;
//SDClass SD1;
SdVolume volume;
String sd_data;
const String file_name;

File myFile;

char lap[4];
char* WIFI_AP = "graham";


#define TOKEN   "Instruino_test"//"Test_Dev" "HBCSE_DEMO"

char thingsboardServer[] = "158.144.43.11"; //"14.139.123.11";//"10.1.0.90";
WiFiEspClient espClient;  // Initialize the Ethernet client object
PubSubClient client(espClient);
int status = WL_IDLE_STATUS;
#define wifi_switch 30

#define ble_switch 27

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float lasthum, lasttemp;

BH1750 lightMeter(0x23);
float lastlux;

// pH Sensor variables

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
float  Offset = 0.00;            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;    

float last_cal_buffer = -1;

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
String last_time_stamp, last_date_stamp, date_stamp, time_stamp;
unsigned char last_day, lastsec, lastmin, lasthour;
const String days[7] = {"SUN", "MON", "TUE", "WED", "THR", "FRI", "SAT"};
Time  t;

boolean wifi_flag =  false, ble_flag = false, sd_flag = false, home_flag = false;
unsigned char wait_screen = 0;

boolean wifi_noti_flag = true, wifi_connect_flag = false, wifi_screen_flag =  false;
boolean sdcard_screen_flag = false, sdcard_noti_flag = false, sdcard_flag =  false;;
boolean log_data = false;
boolean ble_connect_flag = false, ble_noti_flag = true, ble_screen_flag = false;

boolean ph_screen_flag = false, ph_cal_flag = false;
boolean tempprobe_screen_flag = false;
boolean turbidity_screen_flag = false;

static float last_pH, last_voltage, last_offset, cal_buffer;
static float pHValue,voltage;
//static float current_temp = 0.00, last_temp = 0.00;
boolean temp_err = false; 
boolean ds18b20_reader = false, ds18b20_read_display_valid = false, ds18b20_read_display_invalid =  false;

boolean ok  = false; 
String ph_data, ph_logdata, ds_logdata;

int x, y;

char wifi_network_array[4], wifi_network_no = -1;

String time_stamplog = " ", temp_data, turbidity_data, volt_tur;

// For the Adafruit shield, these are the default.
#define TFT_DC 48
#define TFT_CS 53
#define TFT_RST 49
#define TFT_MISO 50
#define TFT_MOSI 51
#define TFT_CLK  52

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 22
#define t_CS 23
#define t_MOSI 24
#define t_MISO 25
#define t_IRQ 26

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

#define turbidityPin A1
float volt = 0.03;
float ntu = 0.05, last_volt_turbidity = 0.00, current_volt_turbidity = 0.00;
boolean turbidity_read_display = false;

String turbidity_logdata, Ds_logdata;

const int stepPin = 8; 
const int dirPin = 9; 

const int cw = 42;
const int ccw = 44;

const int up_limit = 39;
const int dn_limit = 37; 

unsigned char up, down, up_lm, dn_lm;

void setup()
{

   pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  pinMode(up_limit,INPUT_PULLUP); 
  pinMode(dn_limit,INPUT_PULLUP);

  pinMode(cw,INPUT_PULLUP);
  //digitalWrite(cw,HIGH);
  pinMode(ccw,INPUT_PULLUP);
  
  Serial.begin(9600);

  Serial2.begin(9600);
  
  sensors.begin();

  pinMode(wifi_switch, OUTPUT);
  pinMode(ble_switch, OUTPUT);

  pinMode(TFT_CS, OUTPUT);

  pinMode(chipSelect, OUTPUT);

  tft.begin();
  tft.setRotation(3);

  ts.InitTouch();
  ts.setPrecision(PREC_HI);

  rtc.begin();

  test_sensor();

  lightMeter.begin();
}

void loop(void)
{

  sdcardcheck_inloop();

  int select_home_value = 0;

  mandate_data();

  touch_read();

  up_down_mech();

  select_home_value  = touch_result();

  switch (select_home_value)
  {
    case 1: Serial.print("pH Probe");

      //pH_screen_mandate();

      while (wait_screen == 1)
      {

        if (ph_screen_flag == false)
        {
          pH_screen_mandate();
          notification();
          ph_screen_flag = true;
        }

        up_down_mech();

        tdn_window();
        
        htl_window();
        
        pH_read();
        touch_read();

        if ((x >= 130 && x <= 204) && (y >= 190 && y <= 220))
        { 
          
          ok = false;
          last_cal_buffer = -1;
          tft.fillRect(114,185,94,45,ILI9341_GREEN);
          tft.setCursor(115,190);
          tft.print("pH Probe");
          tft.setCursor(146,210);
          tft.print("CAL");

          tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
          tft.setCursor(115,190);
          tft.print("pH Probe");
          tft.setCursor(146,210);
          tft.print("CAL");

          //wait_screen = 0;

          ph_cal_flag = true;
          //cal_buffer = 0.00;
          
          pH_calibration();
           
          while(ok == false)
          {
            notification();

            up_down_mech();
            
            tdn_window();

            //htl_window();
            
            pH_read();

            touch_read();

            pH_cal_buffer_select();

          }
        }  // ***************** END OF Cal Screen *************************************************

        if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220))
        {
          tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
          tft.setCursor(240, 200);
          tft.print("HOME");

          tft.fillRect(215, 185, 98, 45, ILI9341_WHITE);
          tft.setCursor(240, 200);
          tft.print("HOME");

          wait_screen = 0;
          ph_screen_flag = false;
          last_cal_buffer = -1;
        }

        if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220))
        {
          tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
          tft.setCursor(35, 190);
          tft.print("Data");
          tft.setCursor(22, 210);
          tft.print("Logging");

          tft.fillRect(10, 185, 97, 45, ILI9341_WHITE);
          tft.setCursor(35, 190);
          tft.print("Data");
          tft.setCursor(22, 210);
          tft.print("Logging");
        }
      }
      imp_flag();

      break;

    case 2: Serial.print("Temp Probe");
      while (wait_screen == 1)
      {
        if (tempprobe_screen_flag == false)
        {
          tempprobe_screen_mandate();
          notification();
          tempprobe_screen_flag = true;
          //sensors.begin();
          getds18b20_add();
        }

        tdn_window();

        up_down_mech();

        htl_window();

        ds18b20_read();

        touch_read();

        if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220))
        {
          tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
          tft.setCursor(240, 200);
          tft.print("HOME");

          tft.fillRect(215, 185, 98, 45, ILI9341_WHITE);
          tft.setCursor(240, 200);
          tft.print("HOME");

          wait_screen = 0;
          tempprobe_screen_flag = false;
          ds18b20_read_display_valid = false;
          ds18b20_read_display_invalid = false;
          last_temp = 0.00;
        }

        if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220))
        {
          tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
          tft.setCursor(35, 190);
          tft.print("Data");
          tft.setCursor(22, 210);
          tft.print("Logging");

          tft.fillRect(10, 185, 97, 45, ILI9341_WHITE);
          tft.setCursor(35, 190);
          tft.print("Data");
          tft.setCursor(22, 210);
          tft.print("Logging");

          if (log_data == false)
          {
            log_data = true;
            tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
           
            tft.setCursor(35, 190);
            tft.print("Data");
            tft.setCursor(22, 210);
            tft.print("Logging");
          }
        }

        if (log_data == true)
        {
          RTC_data();
          file_name = date_stamp + ".csv";
          time_stamplog = time_stamp;

          Serial.println(file_name);
          Serial.println("opening file");

          pinMode(SS, OUTPUT);
          
          if (!SD.begin(SPI_HALF_SPEED, chipSelect)) 
          {
             Serial.println("initialization failed!");
             tft.fillRect(10, 185, 97, 45, ILI9341_RED);
             tft.setCursor(35, 190);
             tft.print("Data");
             tft.setCursor(22, 210);
             tft.print("Logging");
             log_data = false;
          }
          else
          {
            myFile = SD.open("text1.txt", FILE_WRITE);
  
            if (myFile) 
            {
               myFile.println(time_stamplog);
               myFile.close();
               Serial.println("done.");
            }
          }
         // create_open_file(2, ds_logdata);
        }
      }
      imp_flag();
      break;

    case 3: Serial.print("Turbidity Probe");
      while (wait_screen == 1)
      {
        if (turbidity_screen_flag == false)
        {
          turbidity_screen_mandate();
          notification();
          turbidity_screen_flag = true;
        }

        tdn_window();

        up_down_mech();

        htl_window();

        turbidity_read();

        touch_read();

        if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220))
        {
          tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
          tft.setCursor(240, 200);
          tft.print("HOME");

          tft.fillRect(215, 185, 98, 45, ILI9341_WHITE);
          tft.setCursor(240, 200);
          tft.print("HOME");

          wait_screen = 0;
          turbidity_screen_flag = false;
          turbidity_read_display = false;
          last_volt_turbidity =  0.00;
          log_data = false;
        }

        if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220))
        {
          tft.fillRect(10, 185, 97, 45, ILI9341_YELLOW);
          tft.setCursor(35, 190);
          tft.print("Data");
          tft.setCursor(22, 210);
          tft.print("Logging");

          tft.fillRect(10, 185, 97, 45, ILI9341_WHITE);
          tft.setCursor(35, 190);
          tft.print("Data");
          tft.setCursor(22, 210);
          tft.print("Logging");

          if (log_data == false)
          {
            if (!card.init(SPI_HALF_SPEED, chipSelect))
            {
              log_data = false;
              tft.fillRect(10, 185, 97, 45, ILI9341_RED);
            }
            else
            {
              log_data = true;
              tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
            }
            tft.setCursor(35, 190);
            tft.print("Data");
            tft.setCursor(22, 210);
            tft.print("Logging");
          }
          else
          {
            log_data = false;
          }
        }

        if (log_data == true)
        {
          create_open_file(3, turbidity_logdata);
        }
      }
      imp_flag();
      break;

    case 4: Serial.print("WiFi");

      wifi_noti_flag = true;

      while (wait_screen == 1)
      {
        wifi_screen();
        
        touch_read();

        if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220)) // home
        {
          tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
          tft.setCursor(240, 200);
          tft.print("HOME");

          tft.fillRect(215, 185, 98, 45, ILI9341_WHITE);
          tft.setCursor(240, 200);
          tft.print("HOME");

          wait_screen = 0;
          wifi_screen_flag = false;
          wifi_connect_flag = false;
        }

        if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220))
        {
          tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
          tft.setCursor(35, 190);
          tft.print("WiFi");
          tft.setCursor(22, 210);
          tft.print("ON/OFF");

          tft.fillRect(10, 185, 97, 45, ILI9341_WHITE);
          tft.setCursor(35, 190);
          tft.print("WiFi");
          tft.setCursor(22, 210);
          tft.print("ON/OFF");

          wifi_noti_flag = true;
          wifi_connect_flag = false;
          if (wifi_flag == false)
          {
            digitalWrite(wifi_switch, HIGH);
            wifi_flag = true;
            //---------------------------------------------
            tft.fillRect(48, 65, 313, 90, ILI9341_BLACK);
            tft.setTextColor(ILI9341_LIGHTGREY);
            tft.setTextSize(2);
            tft.setCursor(50, 68);
            tft.print("Initializing WiFi..");
            
            InitWiFi();
            client.setServer(thingsboardServer, 1883 );
            delay(10);

            tft.fillRect(4, 60, 313, 115, ILI9341_BLACK);
            listNetworks();

            tft.fillRect(4, 60, 313, 115, ILI9341_BLACK);
            tft.setTextColor(ILI9341_LIGHTGREY);
            tft.setTextSize(2);
            tft.setCursor(50, 68);
            tft.print("Connecting to AP...");
            //delay(2000);
            //---------------------------------------------
          }
          else
          {
            WiFi.disconnect();
            delay(50);
            digitalWrite(wifi_switch, LOW);
            wifi_flag = false;
            wifi_network_no = -1;
          }

          if (wifi_noti_flag == true)
          {
            notification();
            wifi_noti_flag = false;
          }
        }

        if ((x >= 130 && x <= 204) && (y >= 190 && y <= 220))
        { 
          if(wifi_flag == true)
          {
            WiFi.disconnect();
            delay(50);
            while(WiFi.status() != WL_DISCONNECTED) 
            {
              Serial.println("Connected");
            }
            Serial.println("Disconnected");
            wifi_network_no = -1;
            wifi_connect_flag = false;

            tft.fillRect(114,185,94,45,ILI9341_GREEN);
            tft.setCursor(140,190);
            tft.print("New");
            tft.setCursor(120,210);
            tft.print("Network");

            tft.fillRect(114,185,94,45,ILI9341_LIGHTGREY);
            tft.setCursor(140,190);
            tft.print("New");
            tft.setCursor(120,210);
            tft.print("Network");

            tft.fillRect(4, 60, 313, 115, ILI9341_BLACK);
            tft.setTextColor(ILI9341_LIGHTGREY);
            tft.setTextSize(2);
            tft.setCursor(50, 68);
            tft.print("Initializing WiFi..");
           

            InitWiFi();
            client.setServer(thingsboardServer, 1883 );
            delay(10);

            tft.fillRect(4, 60, 313, 115, ILI9341_BLACK);
            listNetworks();

            tft.fillRect(4, 60, 313, 115, ILI9341_BLACK);
            tft.setTextColor(ILI9341_LIGHTGREY);
            tft.setTextSize(2);
            tft.setCursor(50, 68);
            tft.print("Connecting to AP...");
          }
        }

      }
      imp_flag();
      break;

    case 5: Serial.print("Bluetooth");

      ble_noti_flag = true;

      while (wait_screen == 1)
      {
        ble_screen();
        touch_read();

        if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220))
        {
          tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
          tft.setCursor(12, 190);
          tft.print("Bluetooth");
          tft.setCursor(20, 210);
          tft.print(" ON/OFF");

          tft.fillRect(10, 185, 97, 45, ILI9341_WHITE);
          tft.setCursor(12, 190);
          tft.print("Bluetooth");
          tft.setCursor(20, 210);
          tft.print(" ON/OFF");

          ble_noti_flag = true;
          ble_connect_flag = false;

          if (ble_flag == false)
          {
            digitalWrite(ble_switch, HIGH);
            ble_flag = true;
          }
          else
          {
            digitalWrite(ble_switch, LOW);
            ble_flag = false;
          }
          if (ble_noti_flag == true)
          {
            notification();
            ble_noti_flag = false;
          }
        }

        if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220))
        {
          tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
          tft.setCursor(240, 200);
          tft.print("HOME");

          tft.fillRect(215, 185, 98, 45, ILI9341_WHITE);
          tft.setCursor(240, 200);
          tft.print("HOME");

          wait_screen = 0;
          ble_screen_flag = false;
          ble_connect_flag = false;
        }
      }
      imp_flag();

      break;

    case 6: Serial.print("SD Card");

      while (wait_screen == 1)
      {
        if (sdcard_screen_flag == false)
        {
          sdcard_screen_mandate();
          notification();
          sdcard_screen_flag = true;

          card_info();
        }

        tdn_window();
        touch_read();

        if ((x >= 230 && x <= 308) && (y >= 190 && y <= 220)) // home
        {
          tft.fillRect(215, 185, 98, 45, ILI9341_GREEN);
          tft.setCursor(240, 200);
          tft.print("HOME");

          tft.fillRect(215, 185, 98, 45, ILI9341_WHITE);
          tft.setCursor(240, 200);
          tft.print("HOME");

          wait_screen = 0;
          sdcard_screen_flag = false;
        }

        if ((x >= 19 && x <= 100) && (y >= 190 && y <= 220)) // refresh
        {
          tft.fillRect(10, 185, 97, 45, ILI9341_GREEN);
          tft.setCursor(18, 200);
          tft.print("Refresh");

          tft.fillRect(10, 185, 97, 45, ILI9341_WHITE);
          tft.setCursor(18, 200);
          tft.print("Refresh");

          tft.fillRect(4, 60, 313, 115, ILI9341_BLACK);
          card_info();
        }
      }
      imp_flag();

      break;

    default: break;

  }
}

void test_sensor()
{

  if (lightMeter.begin())
  {
    Serial.println(F("BH1750 OK"));
  }
  else
  {
    Serial.println(F("Error initialising BH1750"));
  }

  dht.begin();
  if (isnan(dht.readHumidity()) || isnan(dht.readTemperature()))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

}

void mandate_data()
{
  if (home_flag == false)
  {
    home_screen();
    notification();
    home_flag = true;
  }

  if (sdcard_noti_flag == true)
  {
    notification();
    sdcard_noti_flag = false;
  }

  htl_window();

  tdn_window();
}

void RTC_data()
{
  t = rtc.getTime();
  date_stamp = t.date / 10;
  date_stamp = date_stamp + t.date % 10 + "/"  + t.mon / 10 + t.mon % 10 + "/" + t.year % 200;

  time_stamp = t.hour / 10;
  time_stamp = time_stamp + t.hour % 10 + ":" + t.min / 10 + t.min % 10 + ":" + t.sec / 10 + t.sec % 10;
}

void screenOn()
{
  digitalWrite(chipSelect, HIGH);
  digitalWrite(TFT_CS, LOW);
}
void cardOn()
{
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(chipSelect, LOW);
}

void up_down_mech()
{
   up = digitalRead(cw);
   up_lm = digitalRead(up_limit);
   while(up == LOW && up_lm == HIGH)
   {  
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
      rotate();
      up = digitalRead(cw);
      up_lm = digitalRead(up_limit);
   }

   //delay(50);

  down =  digitalRead(ccw);
  dn_lm = digitalRead(dn_limit);
  while(down == LOW && dn_lm == HIGH)
  {  
      digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
      rotate();
      down =  digitalRead(ccw);
      dn_lm = digitalRead(dn_limit);
  }
  //delay(50);
}

void rotate()
{
      digitalWrite(stepPin,HIGH); 
      delay(1); 
      digitalWrite(stepPin,LOW); 
      delay(1); 
}
