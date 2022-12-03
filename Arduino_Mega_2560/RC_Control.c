#include <Servo.h>

#define DIR_IN1 4
#define DIR_IN2 5
#define DIR_IN3 6

//create servo objects
Servo steering;
Servo throttle;

int center = 95;

void setup()
{
    Serial.begin(115200);
    pinMode(2, OUTPUT);     //sets pin 9 to output
    pinMode(3, OUTPUT);

    pinMode(DIR_IN1, INPUT);
    pinMode(DIR_IN2, INPUT);
    pinMode(DIR_IN3, INPUT);

    steering.attach(2);   // attach steering servo to pin 9
    throttle.attach(3);  // attach ESC to pin 10

    steering.write(95);   // centers steering
    throttle.write(90);   // sets mid throttle
}

void loop()
{
    uint8_t dir = (digitalRead(DIR_IN3) << 2) | (digitalRead(DIR_IN1) << 1) | digitalRead(DIR_IN2);
    Serial.println(dir);
    if (dir == 3) {
        goForward();
    }
    if (dir == 2) {
        //left
        center = center + 20;
        if (center > 135) {
            center = 135;
        }
        steering.write(center);  // turn left
        delay(10);
        throttle.write(90);  // brake
        delay(10);
    }
    if (dir == 1) {
        //right
        center = center - 20;
        if (center < 60) {
            center = 60;
        }
        steering.write(center);  // turn right
        delay(10);
        throttle.write(90);  // brake
        delay(10);
    }
    if (dir == 4) {
        throttle.write(90);  // go forward 
        delay(10);
        throttle.write(81);  // go forward 
        delay(200);
        throttle.write(90);  // go backward
        delay(200);
        center = 95;
        steering.write(center);
        delay(10);
    }
    if (dir == 0) {
        //stop
        throttle.write(90);
    }
    delay(100);
}

void goForward()  // turn right, then go backward and stop
{
    throttle.write(90);  // go backward
    delay(10);
    throttle.write(102);
    delay(200);
    throttle.write(90);
    delay(200);
    center = 95;
    steering.write(center);
    delay(10);
}