 void Strip_conf(){
  const uint16_t PixelCount = 60; // make sure to set this to the number of pixels in your strip
  NeoGamma<NeoGammaTableMethod> colorGamma;
  NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

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
