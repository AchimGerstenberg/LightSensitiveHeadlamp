#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int pwm = 0;
int target = 600;


void setup() {
  Wire.begin();
  Serial.begin(115200);

  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);

  accelgyro.initialize();
  accelgyro.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);   // largest g range
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    if(ax > 10000 || ay > 10000 || az > 6000)
    { 
     target += 100;
     if(target > 700)
      target = 50;
     delay(150);
    }
  

  
  analogWrite(6, pwm);
  Serial.println(pwm);

  if(analogRead(A0) < target)
   pwm++;

  if(pwm >= 255)
   pwm = 255;
   

  if(analogRead(A0) > target)
   pwm--;
  
  if(pwm <= 10)
   pwm = 10;
  
                   
}
