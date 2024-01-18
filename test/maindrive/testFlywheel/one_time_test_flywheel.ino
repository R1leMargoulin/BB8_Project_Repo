#define drivePWM1 10
#define drivePWM2 11
#define driveEnableR 9
#define driveEnableL 6

#define RIGHT 1
#define LEFT 0


void turn(int speed, int dir){
  if(dir==RIGHT){
      if(speed>100){
        analogWrite(drivePWM1, 50);
        analogWrite(drivePWM2, 0);
      }
      else{
        analogWrite(drivePWM1, speed);
        analogWrite(drivePWM2, 0);
      }
  }
  else if(dir==LEFT){
    if(speed>100){
        analogWrite(drivePWM1, 0);
        analogWrite(drivePWM2, 50);
      }
      else{
        analogWrite(drivePWM1, 0);
        analogWrite(drivePWM2, speed);
      }
  }
  else if((speed < 10) && (speed > -10)){
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

    turn(0, RIGHT);
    delay(1000);
    turn(10,RIGHT);
    delay(3000);
    turn(0,RIGHT);
    delay(2000);
    turn(10, LEFT);
    delay(3000);
    turn(0,LEFT);
    
}

void loop()
{
    delay(1000);
}
