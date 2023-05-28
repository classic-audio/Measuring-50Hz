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

![Princip](https://github.com/classic-audio/Measuring-50Hz/assets/39434972/40ae19b5-ea12-4f7a-8d48-fc210e6b8a20)


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

<H2>Implementation of the code</H2>
1. Measure the sine signal and find the max and min values<br>
2. update the values in the code to the measured values with a margin of min. 100<br>
3. You can use the file:  Code-2023-05-v1.0-ESP32-ADC-Levels.ino<br>
