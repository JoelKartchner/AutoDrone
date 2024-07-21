// Joel and Tate Kartchner
// Self Flying Plane Sketch
// Hardware: 
//  - Arduino Nano(s), Servos, RC Receiver, RC Transmitter, Speedcontrol, Motors
//  - 6 or 9 channel IMU, Pressure Sensor, GPs Sensor
// Features: 
// - Reads 6 channel PPM data from a receiver
// - Processes data and sends commands to servos and speed controller. 
// - Different Modes, controlled by the ax1 and ax2 switches. 
//    - Default Mode: RC Mode
//    - RC Mode: Plane is not autonomous and is controlled fully by the remote. 
//    - Flight Assist Mode: Plane is controlled by remote, but is assisted so it will not hit the ground or roll over. 
//    - Full Auto Mode: Plane flys itself. Will follow route set up in code. 
//      This can either be a fixed flight pattern (like a loop), or use GPS data to go to specific locations.


///////////////////////////////////////////
// Debug Statements
#define DEBUG 1 // For debugging

#define IMU 0 // Toggles code for IMU sensor
#define GPS 0 // Toggles code for GPS sensor
#define ALTIMITER 0 // Toggles code for Altitude Sensor



///////////////////////////////
// Library Includes
#include "ppm.h"

#if IMU
// Libraries for IMU
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
  #endif
#endif

////////////////////////////////////
// Variable Definitions

// PPM Channel Layout
#define THROTTLE    1
#define RUDDER      2
#define ELEVATOR    3
#define AILERON     4
#define AUX1        5
#define AUX2        6
// Pin to run PPM on
#define PPM_PIN A0

#if IMU
// Place IMU Specific #defines here
#endif


////////////////////////////////////////
// Global Variable declarations
unsigned long curr_time = 0;
unsigned long loop_time = 0; // This will keep track of the time (in millis) the loop function takes to run

const unsigned long ppm_tick_interval = 50; // how long (in millis) between ticks
unsigned long ppm_prev_time = 0; // time (in millis) when last tick ran

const unsigned long write_tick_interval = 100; // how long (in millis) between writing channels
unsigned long write_prev_time = 0; // time (in millis) when last write channel function was called

const unsigned long imu_tick_interval = 50;
unsigned long imu_prev_time = 0;

/////////////////////////////////////////
// Channel variables
short throttle = 0;
short rudder = 0;
short elevator = 0;
short aileron = 0;
short aux1 = 0;
short aux2 = 0;

/////////////////////////////////////////////
// IMU Control variables
// THis code should work for MPU6050 6 axis IMUs
#if IMU
MPU6050 mpu;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
#endif

void setup() {
  #if DEBUG
  // Start the serial port to print debug statements
  Serial.begin(115200);
  #endif

  // Start PPM function, with invert signal==false
  ppm.begin(PPM_PIN, false);

}

void loop() {
  // This Function simply runs the interrupt code to call the other functions
  loop_time = millis() - curr_time;
  curr_time = millis();
  // Check if it is time to run ppm
  if(millis() >= ppm_tick_interval + ppm_prev_time) {
    // Update prev_time
    ppm_prev_time = millis();
    // Call read_ppm
    read_ppm();
  }
  // Check if it is time to run write_channels
  if(millis() >= write_tick_interval + write_prev_time) {
    // Update prev_time
    write_prev_time = millis();
    // Call write_channels
    write_channels();
  }
  #if IMU
  // Check if it is time to read the IMU
  if(millis() >= imu_tick_interval + imu_prev_time) {
    imu_prev_time = millis();
    read_imu();
  }
  #endif
}

// This function reads and updates the values for each channel
void read_ppm() {
  throttle  = ppm.read_channel(THROTTLE);
  rudder    = ppm.read_channel(RUDDER);
  elevator  = ppm.read_channel(ELEVATOR);
  aileron   = ppm.read_channel(AILERON);
  aux1      = ppm.read_channel(AUX1);
  aux2      = ppm.read_channel(AUX2);
}

#if IMU
// This function reads the data from the IMU
void read_imu() {

}
#endif

// This function will write the values for each channel to the correct place
void write_channels() {
  #if DEBUG
  // Print the channels to the serial monitor
  Serial.print("LT: ");
  Serial.print(loop_time);
  Serial.print("T: ");
  Serial.print(throttle);
  Serial.print(" R: ");
  Serial.print(rudder);
  Serial.print(" E: ");
  Serial.print(elevator);
  Serial.print(" A: ");
  Serial.print(aileron);
  Serial.print(" 1: ");
  Serial.print(aux1);
  Serial.print(" 2: ");
  Serial.print(aux2);
  Serial.println();
  #endif
}
























