#include "SD.h"
#define SD_ChipSelectPin 53
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

#define echoPin 2
#define trigPin 3
boolean ultraOneIn = true;


void setup(){
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
tmrpcm.speakerPin = 46;
tmrpcm.setVolume(6);

if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}

}

void loop() {
long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

Serial.print(distance);
Serial.println(" cm");

if(distance <6 && ultraOneIn){
    tmrpcm.play("1.wav");
    ultraOneIn = false; 
}else if(distance >6){
    ultraOneIn = true;
}

delay(100);

}
