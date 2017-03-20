#include <SevSeg.h>

SevSeg sevseg; //Instantiate a seven segment object

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int mode = 0;



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  byte numDigits = 4;   
  byte digitPins[] = {A2, A3, A4, A5};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 13};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE; // See README.md for options
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
}

void loop() {
  // read the value from the sensor:
  if(Serial.available()){
    int serialRead = Serial.read();
    if(serialRead == 48)
    {
      mode = 0;
    }else if(serialRead == 49)
    {
      mode = 1;
    }
    Serial.println(serialRead);
  }
  
  if(mode == 0)
  {
    sensorValue = 0;
  }else
  {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    delay(500);
  }
  
  sevseg.setNumber(sensorValue,0);
  sevseg.refreshDisplay();
  if(sensorValue < 200)
  {
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  }
  else if(sensorValue < 260){
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  }else if(sensorValue < 320){
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
  }else {
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
  }
}
