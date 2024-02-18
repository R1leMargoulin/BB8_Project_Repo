#define MainDrivePWM1 12 // PWM Pin for movement, swap the pin numbers on this axis if axis is reversed
#define MainDrivePWM2 13
#define MainDriveEnableR 8
#define MainDriveEnableL 7
#define BalanceDrivePWM1 10
#define BalanceDrivePWM2 11
#define BalanceDriveEnableR 9
#define BalanceDriveEnableL 6

#define RIGHT 1
#define LEFT 0


void turn(int speed, int dir){
  if(dir==RIGHT){
      if(speed>100){
        analogWrite(BalanceDrivePWM1, 50);
        analogWrite(BalanceDrivePWM2, 0);
      }
      else{
        analogWrite(BalanceDrivePWM1, speed);
        analogWrite(BalanceDrivePWM2, 0);
      }
  }
  else if(dir==LEFT){
    if(speed>100){
        analogWrite(BalanceDrivePWM1, 0);
        analogWrite(BalanceDrivePWM2, 50);
      }
      else{
        analogWrite(BalanceDrivePWM1, 0);
        analogWrite(BalanceDrivePWM2, speed);
      }
  }
  else if((speed < 10) && (speed > -10)){
    analogWrite(BalanceDrivePWM1, 0);
    analogWrite(BalanceDrivePWM2, 0);
  }
}


void roll(int speed){
  if(speed>10){
      if(speed>100){
        analogWrite(MainDrivePWM1, 100);
        analogWrite(MainDrivePWM2, 0);
      }
      else{
        analogWrite(MainDrivePWM1, speed);
        analogWrite(MainDrivePWM2, 0);
      }
  }
  else if(speed<-10){
    if(speed< -100){
        analogWrite(MainDrivePWM1, 0);
        analogWrite(MainDrivePWM2, 100);
      }
      else{
        analogWrite(MainDrivePWM1, 0);
        analogWrite(MainDrivePWM2, -speed);
      }
  }
  else if((speed < 10) && (speed > -10)){
    analogWrite(MainDrivePWM1, 0);
    analogWrite(MainDrivePWM2, 0);
  }
}

void setup()
{
    Serial.begin(9600);
    pinMode(MainDrivePWM1, OUTPUT);
    pinMode(MainDrivePWM2, OUTPUT);
    pinMode(MainDriveEnableR, OUTPUT);
    pinMode(MainDriveEnableL, OUTPUT);

    digitalWrite(MainDrivePWM1, LOW);
    digitalWrite(MainDrivePWM2, LOW);

    digitalWrite(MainDriveEnableL, HIGH);
    digitalWrite(MainDriveEnableR, HIGH);

    pinMode(BalanceDrivePWM1, OUTPUT);
    pinMode(BalanceDrivePWM2, OUTPUT);
    pinMode(BalanceDriveEnableR, OUTPUT);
    pinMode(BalanceDriveEnableL, OUTPUT);

    digitalWrite(BalanceDrivePWM1, LOW);
    digitalWrite(BalanceDrivePWM2, LOW);

    digitalWrite(BalanceDriveEnableR, HIGH);
    digitalWrite(BalanceDriveEnableL, HIGH);

}



//data format: [avant,droite] donc [20, -15] balance a gauche en avancant

void loop()
{
    // send data only when you receive data:
    int incomingByte = 0; // for incoming serial data
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte, DEC);
  }
}
