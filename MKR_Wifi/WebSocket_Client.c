#include <ArduinoHttpClient.h>
#include <WiFi101.h>
#include <RPLidar.h>
#include <SPI.h>

#include "arduino_secrets.h"

//Max lidar resolution is 752, to make it easier to send and display in pygame program reduces it to 188 (752/4 = 188)
#define LIDAR_RESOLUTION 80
#define FRAME_LENGTH 120

#define DIR_OUT1 6
#define DIR_OUT2 7
#define DIR_OUT3 8

#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor (MOTOCTRL).


//### WIFI
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int status = WL_IDLE_STATUS;     // the Wifi radio's status
char serverAddress[] = "change_to_ip_address";  // server address (check with ipconfig (windows) or ifconfig (mac, linux))
int port = 8080;

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);

RPLidar lidar;

//### LIDAR
int distances[LIDAR_RESOLUTION];
int signals[LIDAR_RESOLUTION];

void setup() {
    pinMode(DIR_OUT1, OUTPUT);
    pinMode(DIR_OUT2, OUTPUT);
    pinMode(DIR_OUT3, OUTPUT);

    pinMode(RPLIDAR_MOTOR, OUTPUT);  // set pin modes

    //Serial monitor
    Serial.begin(115200);
    //LIDAR serial
    Serial1.begin(115200);
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to Network named: ");
        Serial.println(ssid);  // print the network name (SSID);
        status = WiFi.begin(ssid, pass);
        delay(100);
    }

    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    lidar.begin(Serial1);

}


float minDistance = 100000;
float angleAtMinDist = 0;
void loop() {
    Serial.println("starting WebSocket client");
    client.begin();
    while (client.connected()) {
        if (IS_OK(lidar.waitPoint())) {
            //perform data processing here... 
            float distance = lidar.getCurrentPoint().distance;
            float angle = lidar.getCurrentPoint().angle;  // 0-360 deg
            if (distance > 150 && distance < 5000) { // can be 100000
                minDistance = distance;
                angleAtMinDist = angle;
                client.beginMessage(TYPE_TEXT);
                client.print((String)minDistance + "," + angleAtMinDist);
                client.endMessage();
            }
            minDistance = 100000;
            angleAtMinDist = 0;
        }
        else {
            analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
            // Try to detect RPLIDAR
            rplidar_response_device_info_t info;
            if (IS_OK(lidar.getDeviceInfo(info, 100))) {
                // Detected
                lidar.startScan();
                analogWrite(RPLIDAR_MOTOR, 255);
                delay(1000);
            }
        }
        // check if a message is available to be received
        int messageSize = client.parseMessage();

        if (messageSize > 0) {
            String str = client.readString();
            // Serial.println("Received a message:");
            const char* dir = str.c_str();
            // Serial.println(dir);
            for (int i = 0; i < strlen(dir); i++) {
                char character = dir[i];
                if (character == 'l') {
                    digitalWrite(DIR_OUT1, HIGH);
                    digitalWrite(DIR_OUT2, LOW);
                    digitalWrite(DIR_OUT3, LOW);
                    delay(50);
                }
                if (character == 'r') {
                    digitalWrite(DIR_OUT1, LOW);
                    digitalWrite(DIR_OUT2, HIGH);
                    digitalWrite(DIR_OUT3, LOW);
                    delay(50);
                }
                if (character == 'f') {
                    digitalWrite(DIR_OUT1, HIGH);
                    digitalWrite(DIR_OUT2, HIGH);
                    digitalWrite(DIR_OUT3, LOW);
                    delay(450);
                }
                if (character == 'b') {
                    digitalWrite(DIR_OUT1, LOW);
                    digitalWrite(DIR_OUT2, LOW);
                    digitalWrite(DIR_OUT3, HIGH);
                    delay(450);
                }
                if (character == 's') {
                    digitalWrite(DIR_OUT1, LOW);
                    digitalWrite(DIR_OUT2, LOW);
                    digitalWrite(DIR_OUT3, LOW);
                }
            }
        }
    }
    Serial.println("disconnected");
    delay(5000);
}