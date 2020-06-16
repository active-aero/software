// (c) Chris Phillips 2020  www.active-aero.co.uk
//Threshold based single plane, can drive up to 4 servos however works best with 2.
//This code is open scource, not for comercial resale, please feel free to alter and improve, if you compile a better version please send it to me so that I can share the love!

//This code takes accelerometer data and uses it to drive up to 4 servos for control surfaces in an active aerodynamcs system, the goal is to improve grip under acceleration and braking.
//also to increase stability and grip while cornering

//I also have a more complex version to drive stepper motors instead of servos, however I have found that servos better suit the application, this system can also drive pwm linear actuators.

//info@active-aero.co.uk

#include "Wire.h" // This library allows you to communicate with I2C devices.
#include <Servo.h>
Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int pos1 = 0;    // variable to store the servo position
int pos2 = 0;    // variable to store the servo position
int pos3 = 0;    // variable to store the servo position
int pos4 = 0;    // variable to store the servo position
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
int val;    // variable to read the value from the analog pin
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
 
}
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  myservo1.attach(6);  // attaches the servo on pin 3 to the servo object
  myservo2.attach(9);  // attaches the servo on pin 6 to the servo object
  myservo3.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo4.attach(12);  // attaches the servo on pin 10 to the servo object (all pwm pins)

delay(100);
    myservo1.write(pos1+100);    
    myservo2.write(pos2+100);    
    myservo3.write(pos3+100);
    myservo4.write(pos4+100);  // Start up test, move both wings up
delay(700);
    myservo1.write(pos1-100);
    myservo2.write(pos2-100);
    myservo3.write(pos3-100);
    myservo4.write(pos4-100);  // Start up test, move both wings home

delay(800);    
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  int accX = accelerometer_x; //
  int accY = accelerometer_y; //



//ACTIVE AERO ROUTINE BEGINS



//ACCELERATION DOWNFORCE      
 if (accY>7000||accY<-7000){     // ****** Change these values to alter Y threshold (acceleration and aerobrake)***** try incriments of 2000, higher value is less sensitive.
    myservo1.write(pos1+100);    //                                                                                   posative val= acceleration   negative value = braking 
    myservo2.write(pos2+100);    
    myservo3.write(pos3+100);
    myservo4.write(pos4+100);    // servo movement in degrees
delay(800);
    myservo1.write(pos1-100);
    myservo2.write(pos1-100);
    myservo3.write(pos3-100);
    myservo4.write(pos4-100);         //servo return
  }





// print out data
// Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x)); // ****(DELETE // at start of this line to monitor accelerometer values on serial monitor)****
// Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y)); // ****(DELETE // at start of this line to monitor accelerometer values on serial monitor)****
//Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));

  // delay
//delay(300);  // ****(DELETE // at start of this line to monitor accelerometer values on serial monitor, this will slow down the reaction time by 0.5 seconds also)****
//Serial.println();  // ****(DELETE // at start of this line to monitor accelerometer values on serial monitor)****
}  

// #taste my boolean algebra biatch...
