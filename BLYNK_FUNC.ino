//---------------------------FOR-WIFI-UPDATE---------------------SETUP
void Blynk_conf(){    
    Blynk.begin(auth, ssidblynk, passblynk);
  }
  
//------------------------------BLYNK-FUNC-----------------------------
void mode_switch(int mode)    //---MODE---
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
           //------
           break;
         case 5:
           //------
           break;
         }
    }
//----------------------------BLYNK-VIRTUAL-VAR------------------------

BLYNK_WRITE(V0)   //----OFF
  {
    alloff = param.asInt();
    if (alloff == true){R=0;B=0;G=0;}
  }
BLYNK_WRITE(V1)  //----R
  {
    R = param.asInt();
  }
BLYNK_WRITE(V2)  //----G
  {
    G = param.asInt();
  }
BLYNK_WRITE(V3)  //----B
  {
    B = param.asInt();
  }
BLYNK_WRITE(V4)  //----MODE
  {
    mode = param.asInt();
  }
