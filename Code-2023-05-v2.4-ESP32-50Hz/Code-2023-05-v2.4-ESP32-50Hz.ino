/*  --- Measuring the mains frequency --------------------
 *  Main parts
 *  ESP32 D1
 *  ZMPT101B
 *  TFT display 240x240 - ST7789
 *  ------------------------------------------------------
 *  Design: Classic Audio 2023-05-27
 */
#include <Arduino_ST7789.h>
#include <Adafruit_GFX.h>  
#include <SPI.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSans12pt7b.h>  

// --- Display ------------------------------
#define Black   0x0000
#define Yellow  0xFFE0

// --- Display pin mapping ------------------
#define DC    26   
#define RST   19    
Arduino_ST7789 tft = Arduino_ST7789(DC, RST);    
    
int FC_PIN = 34 ;
volatile float sum = 0.0, freq = 0.0;
const int avg = 50;
float Ringbuffer[avg];
  
void Get50Hz(){
    volatile int64_t start_time, end_time;
    static int idx = 0;
    // --- Measuring ---------------------------------------
    noInterrupts() ;
       while(analogRead(FC_PIN) > 1000); // wait for min
       while(analogRead(FC_PIN) < 2300); // wait for max           
    start_time = esp_timer_get_time();   // get start time
       while(analogRead(FC_PIN) > 1000); // wait for min
       while(analogRead(FC_PIN) < 2300); // wait for max
    end_time = esp_timer_get_time() ;    // get end time
    interrupts(); 
    // --- Calculating the frequency ----------------------- 
    freq = 1000000.0 / (end_time - start_time);
    // --- Updating the buffer -----------------------------    
    Ringbuffer[idx] = freq;
    // --- Counter for the buffer --------------------------
    idx = (idx + 1) % avg; 
}

void setup(){
  Serial.begin(115200);
  pinMode(FC_PIN,INPUT);
  // --- Display ------------------------------------------
  tft.init(240, 240);tft.fillScreen (BLACK);
  // --- PWM - Display dim / fading -----------------------
  ledcSetup(0, 4000, 8);  // ch - PWM freq - resulution
  ledcAttachPin(5, 0);    // Port GPIO 5 - ch
  ledcWrite(0, 100);      // ch - dutycycle      
  // --- Initialize buffer with nominal value for 50Hz ------
  for (int i = 0; i < avg; i++){Ringbuffer[i] = 50.0;}
}

void loop(){
  // --- Measure the mains frequency ---
     Get50Hz();
  // --- Display the mains frequency ---
     tftDisplay();
  // --- Update delay - 5sec -----------
     delay(5000);
}

void tftDisplay(){      
    // --- calculate the average frequency --------------
    for (int i = 0; i < avg; i++){sum += Ringbuffer[i];}
    freq = float(sum / avg);sum = 0.0;
    // --- display the mains frequency ------------------
    tft.setTextColor (Yellow); 
    tft.setFont(&FreeSans12pt7b);   
    tft.setCursor (10,60);tft.print("Mains Frequncy: ");
    tft.setCursor (170,120);tft.print("Hz"); 
    tft.fillRect(40,80,130,45,Black);
    tft.setFont(&FreeSans24pt7b); 
    tft.setCursor (40,120);tft.print(freq,2); 
}
     
