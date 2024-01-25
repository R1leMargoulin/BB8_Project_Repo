#define drivePWM1 10
#define drivePWM2 11
#define driveEnableR 9
#define driveEnableL 6

#define RIGHT 1
#define LEFT 2
#define STRAIGHT 0

#define potPin A8


void turn(int dir){
  if(dir==RIGHT){
        int pot = analogRead(potPin);
        analogWrite(drivePWM1, 0);
        analogWrite(drivePWM2, 30);
        while (pot>437)
        {
         pot = analogRead(potPin);
        }     
        analogWrite(drivePWM1, 0);
        analogWrite(drivePWM2, 0);
  }
  else if(dir==LEFT){
        int pot = analogRead(potPin);
        analogWrite(drivePWM1, 30);
        analogWrite(drivePWM2, 0);
        while (pot<470)
        {
         pot = analogRead(potPin);
        }
        analogWrite(drivePWM1, 0);
        analogWrite(drivePWM2, 0);
  }
  else{
        int pot = analogRead(potPin);
        while (pot> 440 || pot < 450){
            if (pot < 440)
            {
                analogWrite(drivePWM1, 30); //left
                analogWrite(drivePWM2, 0);
            }
            if (pot > 450)
            {
                analogWrite(drivePWM1, 0); 
                analogWrite(drivePWM2, 30); //right
            }
        }
        
        analogWrite(drivePWM1, 0);
        analogWrite(drivePWM2, 0);
  }
}



void setup()
{
    Serial.begin(9600);
    pinMode(drivePWM1, OUTPUT);
    pinMode(drivePWM2, OUTPUT);
    pinMode(driveEnableR, OUTPUT);
    pinMode(driveEnableL, OUTPUT);
    pinMode( potPin, INPUT );

    digitalWrite(drivePWM1, LOW);
    digitalWrite(drivePWM2, LOW);


    digitalWrite(driveEnableL, HIGH);
    digitalWrite(driveEnableR, HIGH);

    turn(RIGHT);
    delay(1000);
    turn(STRAIGHT);
    
}

void loop()
{
    delay(1000);
}

//right:437
//450
//left:475