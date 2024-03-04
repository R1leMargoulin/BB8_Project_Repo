//defines
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


class BB8
{
private:
    float commandState[2];

public:
    BB8(/* args */);
    ~BB8();
    void updateFromSerial();
    void move();
    void roll(int speed);//roll to go front/rear
    void balance(int speed);//balance to turn right/left
    float* get_commandState();
    void set_commandState(float x, float y);

};

BB8::BB8(/* args */)
{
    this->commandState[0] = 0.0;
    this->commandState[1] = 0.0;
}

BB8::~BB8()
{
}

void BB8::move(){ //TODO: Passer en lineaire ou exponentiel/logarithmique pour le joystick
    if(this->commandState[0] >= 0.2){
        this->roll(this->commandState[0]*50); //pourcentage *100 /2
    }
    else if(this->commandState[0] <= -0.2){
        this->roll(this->commandState[0]*50);
    }
    else{
        this->roll(0);
    }
    if(this->commandState[1] <= -0.2){
        this->balance(this->commandState[1]*40);// tester a 30
    }
    else if(this->commandState[1] >= 0.2){
        this->balance(this->commandState[1]*40);//tester a 30
    }
    else{
        this->balance(0);
    }
}

void BB8::updateFromSerial(){
    String strArray[2];
    float floatArray[2];
    String readString = Serial.readString();

    int r=0, t=0;
    for(int i=0;i<readString.length();i++){
        if(readString[i] == ','){
            if (i-r > 1){
                strArray[t] = readString.substring(r,i);
                t++;
            }
            r = (i+1);
        }
    }
    for(int k=0 ;k<=t-1 ;k++){
        //Serial.println(strArray[k]);
        this->commandState[k] = strArray[k].toFloat();
    }
}

void BB8::roll(int speed){
    if(speed>0){//front
        if(speed>100){
            analogWrite(MainDrivePWM1, 100);
            analogWrite(MainDrivePWM2, 0);
        }
        else{
            analogWrite(MainDrivePWM1, speed);
            analogWrite(MainDrivePWM2, 0);
        }
    }
    else if (speed < 0){//rear
        if(abs(speed)> 100){
            analogWrite(MainDrivePWM1, 0);
            analogWrite(MainDrivePWM2, 100);
        }
        else{
            analogWrite(MainDrivePWM1, 0);
            analogWrite(MainDrivePWM2, abs(speed));
        }
    }
    else{//stop
        analogWrite(MainDrivePWM1, 0);
        analogWrite(MainDrivePWM2, 0);
    }
}

void BB8::balance(int speed){
    if(speed>0){//right
        if(speed>100){
        analogWrite(BalanceDrivePWM1, 50);
        analogWrite(BalanceDrivePWM2, 0);
      }
      else{
        analogWrite(BalanceDrivePWM1, speed);
        analogWrite(BalanceDrivePWM2, 0);
      }
    }
    else if (speed < 0){//left
        if(abs(speed)>100){
            analogWrite(BalanceDrivePWM1, 0);
            analogWrite(BalanceDrivePWM2, 50);
        }
        else{
            analogWrite(BalanceDrivePWM1, 0);
            analogWrite(BalanceDrivePWM2, abs(speed));
        }
    }
    else{ //stop
        analogWrite(BalanceDrivePWM1, 0);
        analogWrite(BalanceDrivePWM2, 0);
    }
}


float* BB8::get_commandState(){
    return this->commandState;
}

void BB8::set_commandState(float x, float y){
    this->commandState[0] = x;
    this->commandState[1] = y;
}



BB8 robot = BB8();

void setup()
{
    Serial.begin(115200);
    Serial.setTimeout(100);
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

    robot.move();

}



//data format: [avant,gauche] donc [O.8, 0.5] balance a gauche en avancant

void loop()
{
        //Serial.println("a");
        robot.updateFromSerial();
        robot.move();
        //delay(100);
}