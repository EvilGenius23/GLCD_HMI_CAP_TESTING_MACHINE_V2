//......................................................................................................//
////////////////////////////////////////>> CAP CHECKER MACHINE <</////////////////////////////////////////
//......................................................................................................//

/*THIS CODE IS DESIGNED BY AMOL KADAM
 * firmaware v 2
 * GLCD MCUFRD 
 * ..............
 */

//......................................................................................................//
///////////////////////////////////////////// FIRMWARE V2  ///////////////////////////////////////////////
//......................................................................................................//

#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "bitM.h"
#include "pcb_img.h"
#include "screw_img.h"
#include "a_plate.h"
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>

#include <FreeDefaultFonts.h>


//......................................................................................................//
//////////////////////////////////////CREATE SCREEN OBJECT ///////////////////////////////////////////////
//......................................................................................................//


MCUFRIEND_kbv tft; 


//......................................................................................................//
//////////////////////////////////////CALIBRATION TOUCH SCREEN////////////////////////////////////////////
//......................................................................................................//


const int XP=7,XM=A1,YP=A2,YM=6; //240x320 ID=0x5408
const int TS_LEFT=969,TS_RT=181,TS_TOP=927,TS_BOT=310;


//......................................................................................................//
///////////////////////////////////////////END CALIBRATION ///////////////////////////////////////////////
//......................................................................................................//

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_GFX_Button buttons[16];
TSPoint tp;

//......................................................................................................//
////////////////////////////////////////////// MACROS ////////////////////////////////////////////////////
//......................................................................................................//

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define TEXT_X 5
#define TEXT_Y 25
#define TEXT_W (tft.width()-10)
#define TEXT_H 70
#define TEXT_TSIZE 3
#define TEXT_TCOLOR BLUE
#define TEXT_LEN 10

//......................................................................................................//
////////////////////////////////////////// DATA_VARIABLES ////////////////////////////////////////////////
//......................................................................................................//


const int A = 31, B = 33 , C = 35 , STD = 53 ;    // the number of the pushbutton pin
int A_STATE , B_STATE , C_STATE = 0 ;            //BTN STATE 


//......................................................................................................//
///START SETUP CODE////START SETUP CODE /////START SETUP CODE////START SETUP CODE////START SETUP CODE/////
/////////START SETUP CODE///////START SETUP CODE//////START SETUP CODE///////////START SETUP CODE/////////
//......................................................................................................//

void setup() {
  
Serial.begin(9600); //SET BAUD RATE 9600 

// INITIALISE PIN MODE 
      pinMode(A, INPUT);
      pinMode(B, INPUT);
      pinMode(C, INPUT);
      pinMode(STD, OUTPUT);
      tft.reset();
      uint16_t ID = tft.readID();
      Serial.print("TFT ID = 0x");
      Serial.println(ID, HEX);
    
    if (ID == 0xD3D3) ID = 0x9486; // write-only shield
      tft.begin(ID);
      tft.setRotation(3);           //PORTRAIT
      tft.fillScreen(WHITE);

      plash_screen(); //Call Welcome Screen

      delay(5000);  //wait for touch


}

//......................................................................................................//
///END SETUP CODE/////END SETUP CODE /////////END SETUP CODE///////END SETUP CODE/////END SETUP CODE//////
/////////END SETUP CODE///////////END SETUP CODE////////END SETUP CODE/////////////END SETUP CODE/////////
//......................................................................................................//





//......................................................................................................//
///START MAIN LOOP////START MAIN LOOP /////START MAIN LOOP////START MAIN LOOP////START MAIN LOOP//////////
/////////START MAIN LOOP///////START MAIN LOOP//////START MAIN LOOP///////////START MAIN LOOP/////////////
//......................................................................................................//

void loop() {
//tft.reset();
//READ PIN STATUS AT EVERY SCAN 

      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);

///////////////////////////////////////////// WHAT IF ?(000) //////////////////////////////////////////////
 
 if (A_STATE == LOW && B_STATE == LOW && C_STATE == LOW ) {
    
    /*
     * 
     * STANDBY SCREEN
     * TEXT GRAPHICS
     * 
     */
    
    screen_a(); //Call Screen 1 
    
    while(A_STATE == LOW && B_STATE == LOW && C_STATE == LOW) //WHILE YOU WAIT KEEP EYE ON CONTION AS WELL
    {
      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);
    }
    
  }

///////////////////////////////////////////// WHAT IF ?(001) //////////////////////////////////////////////   

  if (A_STATE ==HIGH && B_STATE == LOW && C_STATE ==LOW  ) 
{

    /*
     * 
     * LOAD HOUSING 
     * TEXT GRAPHICS
     * 
     */
 
      screen_b();  //call screen 2
   while(A_STATE ==HIGH && B_STATE == LOW && C_STATE ==LOW) //WHILE YOU WAIT KEEP EYE ON CONTION AS WELL
       {
      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);
    }
}

///////////////////////////////////////////// WHAT IF ?(010) //////////////////////////////////////////////  
 
if (A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW ) 

{
    
    /*
     * 
     * CONTION 1ST , SHOW 
     * TEXT GRAPHICS
     * 
     */
     
    screen_c(); //SHOW 3rd SCREEN 
    
    while(A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW ) //WHILE YOU WAIT KEEP EYE ON CONTION AS WELL
    {
      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);
    }
 }

///////////////////////////////////////////// WHAT IF ?(011) //////////////////////////////////////////////
     
 if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW ) 
{
      
    /*
     * PLACE PCBA ON LH HOUSING  
    * TEXT GRAPHICS
    * 
    */
    
      screen_d(); //show screen 4
      
    while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW ) //WHILE YOU WAIT KEEP EYE ON CONTION AS WELL
    {
      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);
     }
     
}
    

///////////////////////////////////////////// WHAT IF ?(100) ////////////////////////////////////////////// 
   
    if (A_STATE ==LOW && B_STATE == LOW && C_STATE == HIGH ) 
{
      
      /*
       * "INSTALL LAMP" TEXT
       */
    while(A_STATE ==LOW && B_STATE == LOW && C_STATE == HIGH )  //WHILE YOU WAIT KEEP EYE ON CONTION AS WELL
    {
      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);
    }
}
    

/////////////////////////////////////////////WHAT IF ? (101) ////////////////////////////////////////////// 
    
if (A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH ) 
{
      
    /* 
     *  UNLOCK THE PRODUCT YOU ARE DONE 
     *  END DISPLAY GRAPHICS
     *  
     */
    
   while(A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH ) //WHILE YOU WAIT KEEP EYE ON CONTION AS WELL
   {
      A_STATE = digitalRead(A);
      B_STATE = digitalRead(B);
      C_STATE = digitalRead(C);
   }
  
}

///////////////////////////////////////////// WHAT IF NOTHIG ? ////////////////////////////////////////////

  else 
  {
    
    // NOTHING TO DO THEN I WILL PLAY WITH LED :)
    digitalWrite(STD, LOW);
  /*UNREACHABLE CODE 
   * DO NOT TAKKE LOAD :)
   */
}
}

//......................................................................................................//
///END MAIN LOOP////END MAIN LOOP /////END MAIN LOOP////END MAIN LOOP////END MAIN LOOP////END MAIN LOOP///
////////END MAIN LOOP///////END MAIN LOOP//////END MAIN LOOP////////END MAIN LOOP////END MAIN LOOP////////
//......................................................................................................//





//......................................................................................................//
///START SUBROUTINE FUNCTIONS/////////START SUBROUTINE FUNCTIONS////START SUBROUTINE FUNCTIONS////////////
///////////////START SUBROUTINE FUNCTIONS//////////////START SUBROUTINE FUNCTIONS/////////////////////////
//......................................................................................................//


void plash_screen()
{
  
      uint16_t width  = tft.width()  - 1;
      uint16_t height = tft.height() - 1;
      uint8_t  border = 10;
      
      tft.fillScreen(0x4A1C);
      tft.fillRect(border, border, (width - border * 2), (height - border * 2), 0x44DC); 
      tft.drawRoundRect(40, 125, 250, 25,10, RED);
      tft.drawRGBBitmap(125,20, marilyn_64x64, 64,64);
      tft.setTextSize (2);
      tft.setTextColor(RED);
      showmsgXY((tft.width()/2)-128, 110, 1, &FreeSerif12pt7b, "AMAR JIGS & FIXTURES",BLACK);
      showmsgXY((tft.width()/2)-85,140, 1, &FreeSans9pt7b, "www.ajfindia.com",GREEN);
      showmsgXY((tft.width()/2)-50, 200, 1, &FreeSerif12pt7b, "LOADING...",BLACK);
      
      
      
}

//......................................................................................................

void screen_a()
{
      tft.fillScreen(WHITE);
      tft.fillRect(0, 0, 320,  50, 0x44DC);    //HEADER TAB
      tft.fillRect(0, 190, 320,  50, 0x44DC);  //FOOTER TAB
      tft.fillRect(315-131, 55-3, 134,134, BLACK); //IMAGE BASE (BLACK)
      tft.fillRoundRect(5, 55-3, 173,134, 15, 0x1384); //BIG ROUND RECT (DARK GREEN)
      tft.fillRoundRect(16, 56, 150,25, 15, 0x5828); // SMALL ROUND RECT (PURPAL)

      
      tft.drawRGBBitmap(315-128,55, marilyn_64x64, 64,64);          // IMAGE WANT TO DRAW IN A PIECES (X1)
      tft.drawRGBBitmap(315-64,55, plate_img, 64,64);               //(X2)
      tft.drawRGBBitmap(315-64,55+64, pcb_img, 64,64);              //(X3)
      tft.drawRGBBitmap(315-128,55+64, screw_img, 64,64);           //(X4)
      

      tft.setCursor (320-60,30);
      tft.setTextSize (1.5);
      tft.setTextColor(RED);
        showmsgXY((tft.width()/2)+40 ,39+5, 1, &FreeSans9pt7b, "PROCESS" , BLACK);
       //  showmsgXY(320-115,50, 1, &FreeSevenSegNumFont, "234",RED);
        showmsgXY(5,39+5, 1, &FreeSans9pt7b, "LOGO" , BLACK);
        
//......................................................................................................        
//          <Fn>  |  <X>  |  <Y>  | <SIZE> |     <FONT>      |   < COUSTOM TEXT >        | <COLOR >| 
//......................................................................................................          
        showmsgXY (  210  ,  235  ,   1    ,  &FreeSans9pt7b  ,  "CYCLE TIME"            ,  BLACK  );
        showmsgXY (  5    ,  235  ,   1    ,  &FreeSans9pt7b  ,  "PRODUCTION"            ,  BLACK  );
        showmsgXY (  65   ,  74   ,   1    ,  &FreeSans9pt7b  ,  "TITLE"                 ,  WHITE  );
        showmsgXY (  12   ,  110  ,   1    ,  &FreeSans9pt7b  ,  "This is sample Text"   ,  WHITE  );
        showmsgXY (  12   ,  130  ,   1    ,  &FreeSans9pt7b  ,  "Visualisation trial "  ,  WHITE  );
        showmsgXY (  12   ,  150  ,   1    ,  &FreeSans9pt7b  ,  "Made by Amol "         ,  WHITE  );
        showmsgXY (  12   ,  170  ,   1    ,  &FreeSans9pt7b  ,  "Do as per image "      ,  WHITE  );
        showmsgXY (  12   ,  190  ,   1    ,  &FreeSans9pt7b  ,  "Shown "                ,  WHITE  );
//......................................................................................................

//      tft.setTextSize (3);
//      tft.setTextColor(RED);
//      tft.setCursor ((tft.width()/2)-90, 130+10);
//      tft.println("WE ARE TECH");
//      tft.setCursor ((tft.width()/2)-90, 165+10);
//      tft.println("  BURNERS");

}

//......................................................................................................

void screen_b()
{
      tft.fillScreen(WHITE);
      tft.setCursor ((tft.width()/2)-60, 18);
      tft.setTextSize (2);
      tft.setTextColor(BLACK);
      tft.println("ALARM SCREEN");
      tft.drawRoundRect(TEXT_X, 10, TEXT_W, 30, 10, RED);
      tft.drawRGBBitmap(125,55, marilyn_64x64, 64,64);

      tft.setTextSize (3);
      tft.setTextColor(RED);
      tft.setCursor ((tft.width()/2)-96,140);
      tft.println("IN THE FIELD");
      tft.setCursor ((tft.width()/2)-91, 175);
      tft.println("     OF");
      tft.setCursor ((tft.width()/2)-91, 205);
      tft.println(" AUTOMATION");

}

//......................................................................................................

void screen_c()
{
      tft.fillScreen(WHITE);
      tft.setCursor ((tft.width()/2)-95, 18);
      tft.setTextSize (2);
      tft.setTextColor(BLACK);
      tft.println("PRODUCTION SCREEN");
      tft.drawRoundRect(TEXT_X, 10, TEXT_W, 30, 10, RED);
      tft.drawRGBBitmap(125,20, marilyn_64x64, 64,64);

      tft.setTextSize (3);
      tft.setTextColor(RED);
      tft.setCursor (20, 85);
      tft.println("WHASH YOUR HANDS");
      tft.setCursor ((tft.width()/2)-91, 120);
      tft.println("   TWISE");
      tft.setCursor ((tft.width()/2)-91, 120+35);
      tft.println("  IN A DAY");
}

//......................................................................................................

void screen_d()
{
  
      tft.fillScreen(WHITE);
      tft.fillRoundRect(TEXT_X, 10, TEXT_W, 30, 10, RED);
      tft.drawRGBBitmap(125,20, marilyn_64x64, 64,64);
      tft.setCursor (80, 18);
      tft.setTextSize (2);
      tft.setTextColor(BLACK);
      tft.println("SETTING SCREEN");
      tft.drawRGBBitmap(125,50, pcb_img, 64,64);
//    tft.drawRGBBitmap(125,50, screw_img, 64,64);
//    tft.drawRGBBitmap(125,50, plate_img, 64,64);

      tft.setTextSize (3);
      tft.setTextColor(RED);
      tft.setCursor (20, 85+40);
      tft.println("PLEASE WERE MASK");
      tft.setCursor ((tft.width()/2)-20, 120+40);
      tft.println("IN");
      tft.setCursor ((tft.width()/2)-120, 120+35+40);
      tft.println(" PUBLIC PLACE");

}

//......................................................................................................

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg,unsigned int clr)
{
    int16_t x1, y1;
    uint16_t wid, ht;
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(clr);
    tft.setTextSize(sz);
    tft.print(msg);
    delay(1);
}


//......................................................................................................//
///END SUBROUTINE FUNCTIONS/////////END SUBROUTINE FUNCTIONS////END SUBROUTINE FUNCTIONS//////////////////
///////////////END SUBROUTINE FUNCTIONS//////////////END SUBROUTINE FUNCTIONS/////////////////////////////
//......................................................................................................//
