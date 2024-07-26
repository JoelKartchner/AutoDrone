# AutoDrone

### Created by Joel and Tate Kartchner

This project uses arduinos to convert an RC plane into an autonomous drone. 

##### Test 1
This is a test to make sure that we can interface between the receiver and the arduino. The code is set up to receive and parse PPM data and print out the values for 6 different channels. To set it up, the arduino/ESP32 (microcontroller) needs to be connected to the PPM/Data channel of the receiver. The microcontroller can power the receiver for this test. As of 7/25/24 the code will compile for an arduino nano, but not for an ESP32. This is because the ppm library I am using right now is not compatible with non-avr boards. 
