
    //---------------------------FOR-WIFI-UPDATE---------------------INCLUDES
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "Bruno";
const char* password = "1997mup1997";
    //---------------------------FOR-WIFI-UPDATE---------------------INCLUDES
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

char auth[] = "365352f0ba2245a785f3702f6859eb13";// BLYNK
char ssidblynk[] = "Bruno";// BLYNK
char passblynk[] = "1997mup1997";// BLYNK

    int R = 0;
    int G = 0;
    int B = 0; 
    bool truecolor = true;
    bool alloff;
    int mode = 0;
     //---------------------------LED---------------------
      const uint16_t PixelCount = 60; // make sure to set this to the number of pixels in your strip
      NeoGamma<NeoGammaTableMethod> colorGamma;
      NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
      
      void DrawPixels(bool corrected, int R, int G, int B)//SET ALL LEDS COLOR
      {
          for (uint16_t index = 0; index < strip.PixelCount(); index++)
          {
              RgbColor color = RgbColor(R,G,B);
              if (corrected){color = colorGamma.Correct(color);}strip.SetPixelColor(index, color);
          }
          strip.Show();
      }
      
      void DrawPixelsWhell(int steps)                      //MAKE ALL COLOR WHELL
      {
        int ml = 110;
        int ll = 20;
        for(int c=0; c<=5; c++)
          for(int i=ll; i<ml; i+=steps)
          {
            switch(c)
              {
                case 0:
                  DrawPixels(true, ml , i, 0);
                  break; 
                case 1:
                  DrawPixels(true, ml - i + ll , ml, 0);
                  break; 
                case 2:
                  DrawPixels(true, 0 , ml, i);
                  break;
                case 3:
                  DrawPixels(true, 0 , ml - i + ll, ml);
                  break; 
                case 4:
                  DrawPixels(true, i , 0, ml);
                  break;
                case 5:
                  DrawPixels(true, ml , 0, ml - i + ll);
                  break;
              }
              delay(50);
            }
      }
     //---------------------------LED---------------------

void setup() {
    //---------------------------FOR-WIFI-UPDATE---------------------SETUP
        Serial.begin(115200);
        Serial.println("Booting");
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        while (WiFi.waitForConnectResult() != WL_CONNECTED) {
          Serial.println("Connection Failed! Rebooting...");
          delay(5000);
          ESP.restart();
        }
        // Port defaults to 8266
        // ArduinoOTA.setPort(8266);
           ArduinoOTA.setHostname("esp8266");
      
        // No authentication by default
        // ArduinoOTA.setPassword("admin");
      
        // Password can be set with it's md5 value as well
        // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
        // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");
      
        ArduinoOTA.onStart([]() {
          String type;
          if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
          else // U_SPIFFS
            type = "filesystem";
      
          // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
          Serial.println("Start updating " + type);
        });
        ArduinoOTA.onEnd([]() {
          Serial.println("\nEnd");
        });
        ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
          Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        });
        ArduinoOTA.onError([](ota_error_t error) {
          Serial.printf("Error[%u]: ", error);
          if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
          else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
          else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
          else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
          else if (error == OTA_END_ERROR) Serial.println("End Failed");
        });
        ArduinoOTA.begin();
        Serial.println("Ready");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
      //---------------------------FOR-WIFI-UPDATE---------------------SETUP
    Blynk.begin(auth, ssidblynk, passblynk);
    strip.Begin();
    strip.Show();
}
 //-----------------------------BLYNK-VAR---------------------------
BLYNK_WRITE(V0)
  {
    alloff = param.asInt();
    if (alloff == true){R=0;B=0;G=0;}
  }
BLYNK_WRITE(V1)
  {
    R = param.asInt();
  }
  BLYNK_WRITE(V2)
  {
    G = param.asInt();
  }
  BLYNK_WRITE(V3)
  {
    B = param.asInt();
  }
  BLYNK_WRITE(V4)
  {
    mode = param.asInt();
  }
  void mode_switch(int mode)
  {
    switch(mode)
              {
                case 1:
                  DrawPixels(true, 0 , 0, 0);
                  delay(500);
                  break; 
                case 2:
                  DrawPixels(true, R , G, B);
                  delay(500);
                  break;
                case 3:
                  DrawPixelsWhell(2);
                  break; 
                case 4:
                 
                  break;
                case 5:
                
                  break;
              }
    }
//-----------------------------BLYNK-VAR--------------------------- 

void loop() {
  ArduinoOTA.handle();    //---FOR-WIFI-UPDATE---
  Blynk.run();

  mode_switch(mode);
  
}
