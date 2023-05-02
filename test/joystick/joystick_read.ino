struct joystick_read
{
    /* data */
public:
    joystick_read::joystick_read()
    {
        xSpeed = 0;
        ySpeed = 0;
    }
    float entryToSpeedX(float entry)
    {
        float res = entry - 520;
        return res;
    }
    float entryToSpeedY(float entry)
    {
        float res = entry - 520;
        return res;
    }

    float setXSpeed(float analogentry)
    {
        this->xSpeed = this->entryToSpeedX(analogentry) / 510 * 100;
    }
    float setYSpeed(float analogentry)
    {
        this->ySpeed = this->entryToSpeedY(analogentry) / 510 * 100;
    }

    float getXSpeed()
    {
        return this->xSpeed;
    }
    float getYSpeed()
    {
        return this->ySpeed;
    }

private:
    float xSpeed;
    float ySpeed;
};

// SETUP VARIABLES
int xpin = A1;
int ypin = A2;
joystick_read joy = joystick_read();

void setup()
{
    // initialize digital pin LED_BUILTIN as an output.
    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
    Serial.println("Mesures");
    float x = analogRead(xpin);
    float y = analogRead(ypin);
    joy.setXSpeed(x);
    joy.setYSpeed(y);
    Serial.println("x");
    // Serial.println(x);
    Serial.println(joy.getXSpeed());
    Serial.println("y");
    // Serial.println(y);
    Serial.println(joy.getYSpeed());
    delay(1000); // wait for a second
}
