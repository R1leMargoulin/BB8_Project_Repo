#define STOP 13
#define LEFT 8
#define RIGHT 10
#define FRONT 12
#define REAR 11


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

void BB8::move(){
    if(this->commandState[0] >= 0.4){
        this->roll(1);
    }
    else if(this->commandState[0] <= -0.4){
        this->roll(-1);
    }
    else{
        this->roll(0);
    }
    if(this->commandState[1] >= 0.4){
        this->balance(1);
    }
    else if(this->commandState[1] <= -0.4){
        this->balance(-1);
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
        Serial.println(strArray[k]);
        this->commandState[k] = strArray[k].toFloat();
    }
}

void BB8::roll(int speed){
    if(speed>0){//front
        digitalWrite(REAR, LOW);
        digitalWrite(STOP, LOW);
        digitalWrite(FRONT, HIGH);
    }
    else if (speed < 0){//rear
        digitalWrite(FRONT, LOW);
        digitalWrite(STOP, LOW);
        digitalWrite(REAR, HIGH);
    }
    else{
        digitalWrite(REAR, LOW);
        digitalWrite(FRONT, LOW);
        digitalWrite(STOP, HIGH);
    }
}

void BB8::balance(int speed){
    if(speed>0){//right
        digitalWrite(STOP, LOW);
        digitalWrite(LEFT, LOW);
        digitalWrite(RIGHT, HIGH);
    }
    else if (speed < 0){//left
        digitalWrite(STOP, LOW);
        digitalWrite(RIGHT, LOW);
        digitalWrite(LEFT, HIGH);
    }
    else{
        digitalWrite(RIGHT, LOW);
        digitalWrite(LEFT, LOW);
        digitalWrite(STOP, HIGH);
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
    Serial.begin(9600);
    pinMode(STOP, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(RIGHT, OUTPUT);
    pinMode(FRONT, OUTPUT);
    pinMode(REAR, OUTPUT);

    digitalWrite(STOP, LOW);
    digitalWrite(LEFT, LOW);
    digitalWrite(RIGHT, LOW);
    digitalWrite(FRONT, LOW);
    digitalWrite(REAR, LOW);
    robot.move();

}



//data format: [avant,droite] donc [20, -15] balance a gauche en avancant

void loop()
{
    while (Serial.available()){
        //Serial.println(robot.get_commandState()[0]);
        robot.updateFromSerial();
        robot.move();
    }
}