#include <Ultrasonic.h>
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <SD.h>

char auth[] = ""; //auth. token for your app

char ssid[] = ""; // wifi name
char pass[] = ""; // wifi password

BlynkTimer usTimer;


const int door = D2;
const int ac = D3;
const int garage = D4;
const int light = D8;
//ultrasonic
const int triggerPin = D0;
const int echoPin = D1;

Ultrasonic ultrasonic(triggerPin, echoPin);

void sendUss(){ //distance
  int distance = ceil(ultrasonic.read());
  if(distance <= 80){
    digitalWrite(door, HIGH);
  }else{
    digitalWrite(door, LOW);
  }
  Serial.println(distance);
  Blynk.virtualWrite(V1, min(300, distance));
}

BLYNK_WRITE(V4){ //ac
  int pinValue = param.asInt();
  if(pinValue){
    digitalWrite(ac, HIGH);
  }else{
    digitalWrite(ac, LOW);
  }
}

BLYNK_WRITE(V3){ //garage
  int pinValue = param.asInt();
  if(pinValue){
    digitalWrite(garage, HIGH);
  }else{
    digitalWrite(garage, LOW);
  }
}

BLYNK_WRITE(V2){ //light
  int pinValue = param.asInt();
  if(pinValue){
    digitalWrite(light, HIGH);
  }else{
    digitalWrite(light, LOW);
  }
}

void setup() {
  Blynk.begin(auth, ssid, pass);
  delay(1000);
  
  Serial.begin(9600);

  
  pinMode(door, OUTPUT);
  pinMode(ac, OUTPUT);
  pinMode(garage, OUTPUT);
  pinMode(light, OUTPUT);
  
  usTimer.setInterval(300L, sendUss);
}

void loop() {
  Blynk.run();
  usTimer.run();
}
