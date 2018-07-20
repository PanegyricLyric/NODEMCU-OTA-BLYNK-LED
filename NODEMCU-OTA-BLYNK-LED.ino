    //---------------------------FOR-WIFI-UPDATE---------------------INCLUDES
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
const char* ssid = "Bruno";
const char* password = "1997mup1997";
    //---------------------------FOR-BLYNK---------------------------INCLUDES
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "365352f0ba2245a785f3702f6859eb13";// BLYNK
char ssidblynk[] = "Bruno";// BLYNK
char passblynk[] = "1997mup1997";// BLYNK
    //---------------------------FOR-LED-----------------------------INCLUDES
#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

const uint16_t PixelCount = 60; // make sure to set this to the number of pixels in your strip
NeoGamma<NeoGammaTableMethod> colorGamma;
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

    int R = 0, G = 0, B = 0;
    bool truecolor = true;
    bool alloff;
    int mode = 0;
    
//--------------------------------------------------------------------------------------S---E---T---U---P-----
void setup() {
    Serial.begin(115200);
    OTA_Conf();
    Blynk_conf();
    Strip_conf();
}
//-----------------------------------------------------------------------------------------L---O---O---P------
void loop() {
  ArduinoOTA.handle();    //---FOR-WIFI-UPDATE---
  Blynk.run();            //---BLYNK-RUN---------
  mode_switch(mode);      //---MODE-SWITCH-------
}
