/* Measuring the ADC max and min values of the signal */

void setup(){
  Serial.begin(115200);
  pinMode(34,INPUT);
}

void loop(){
  for(int x = 0; x < 10;x++){
      SignalLevel();
  }
      while(1);
}

void SignalLevel(){
   // --- sub variables ---------------------------------
   unsigned long startMillis= millis();                                    
   int VinWindow = 1000;
   unsigned int Vpp = 0, Vmax = 0, Vmin = 4096, Vin = 0;                          
   // --- Measuring ------------------------------------- 
   while (millis() - startMillis < VinWindow){
   Vin = analogRead(34);                                                    
      Vmax = max(Vin,Vmax);
      Vmin = min(Vin,Vmin);                                            
   }
   Serial.print(Vmin);Serial.print("__");Serial.println(Vmax);
} 
