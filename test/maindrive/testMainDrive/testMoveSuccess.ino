#define drivePWM1 12 // PWM Pin for movement, swap the pin numbers on this axis if axis is reversed
#define drivePWM2 13
#define driveEnableR 8
#define driveEnableL 7


void roll(int speed){
  if(speed>0){
    analogWrite(drivePWM1, 100);
    analogWrite(drivePWM2, 0);
  }
  else if(speed<0){
    analogWrite(drivePWM1, 0);
    analogWrite(drivePWM2, 100);
  }
  else if(speed==0){
    analogWrite(drivePWM1, 0);
    analogWrite(drivePWM2, 0);
  }
}

void setup()
{
    pinMode(drivePWM1, OUTPUT);
    pinMode(drivePWM2, OUTPUT);
    pinMode(driveEnableR, OUTPUT);
    pinMode(driveEnableL, OUTPUT);

    digitalWrite(drivePWM1, LOW);
    digitalWrite(drivePWM2, LOW);

    // PID3.SetMode(AUTOMATIC);              // PID Setup - main drive motor
    // PID3.SetOutputLimits(-255, 255);
    // PID3.SetSampleTime(15);

    digitalWrite(driveEnableL, HIGH);
    digitalWrite(driveEnableR, HIGH);

    roll(0);
    delay(1000);
    roll(20);
    delay(4000);
    roll(0);
}




void loop()
{
    delay(1000);
}
