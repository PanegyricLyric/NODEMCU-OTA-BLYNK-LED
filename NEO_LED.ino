 void Strip_conf(){
    strip.Begin();
    strip.Show();
  }
 //----------------------------------------------LED-FUNC------------------------------------------------
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
            switch(c){
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


void DrawPixelsBreath(bool corrected, int R, int G, int B)//SET ALL LEDS COLOR
      {      
        //  Regular (orange) flame:
          int r = 226, g = 60, b = 12;
        //  Purple flame:
        //  int r = 158, g = 8, b = 148;
        //  Green flame:
        //int r = 74, g = 150, b = 12;
      
        //  Flicker, based on our initial RGB values
        for (uint16_t index = 0; index < strip.PixelCount(); index++){
          int flicker = random(0,55);
          int r1 = r-flicker;
          int g1 = g-flicker;
          int b1 = b-flicker;
          if(g1<0) g1=0;
          if(r1<0) r1=0;
          if(b1<0) b1=0;
          
          RgbColor color = RgbColor(r1,g1, b1);
          strip.SetPixelColor(index,color);
        }
        strip.Show();
        delay(random(10,113));
} 
//---------------------------------------------ADA-NEO-----------------------------
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
  
  for(int i = 0; i < NUM_LEDS+NUM_LEDS; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUM_LEDS; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUM_LEDS) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    showStrip();
    delay(SpeedDelay);
  }
}

void fadeToBlack(int ledNo, byte fadeValue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}
