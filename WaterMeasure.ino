#include <TimerOne.h>
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

  Timer1.initialize(1000000);
  Timer1.attachInterrupt(transmitSerial); // after 1 second,it will perform 'transmitSerial' function
}

void transmitSerial()
{
  Serial.println(sensorValue); // show value of water level in Serial Monitor
}

void loop() {
  // read the value from the sensor:
  if(Serial.available()){            // read 1 or 0 from serial monitor and define mode
    int serialRead = Serial.read();
    if(serialRead == 48)
    {
      mode = 0;                     // stop showing the value of water level
    }else if(serialRead == 49)
    {
      mode = 1;                     // show the value of water level
    }
    //Serial.println(serialRead);
  }
  
  sensorValue = (mode==0) ? 0 : analogRead(sensorPin); // if water level is 0, sensorValue = 0
                                                       // else sensorValue = value from pin A0
  sevseg.setNumber(sensorValue,0); // display value on seven segment from sensorValue
  sevseg.refreshDisplay();         // refresh displayed value for show new value
  if(sensorValue < 250)
  {
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  }
  else if(sensorValue < 350){
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  }else if(sensorValue < 425){
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
  }else {
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
  }
}
