# Measuring-50Hz
This code measures the mains frequency of 50Hz.<br>
The signal source is a SINE wave.<br>
The sine wave from the output of ZMPT101B<br>
<br>
<B>Main parts:</B><br>
ESP32 - D1<br>
ZMPT101B<br>
TFT display 240x240 - ST7789<br>
<br><br>

This is how the code measures the mains frequency.<br>
The signal is a direct output from ZMPT101B<br>
![Princip](https://github.com/classic-audio/Measuring-50Hz/assets/39434972/d958b991-96d9-4ea5-8f58-9b02ad144cfe)
<br>
The code search for the first LOW level of the code<br>
When this is found - the code continius to look for the max of the signal or a level a little below max.<br>
Then the START time (usec) is saved.<br>
<br>
Then the code search for the HIGH level of the code<br>
Then the END time (usec) is saved.<br>
<br><br>
The code can measure relativly low frequences - up to 1kHz.
<br><br>

