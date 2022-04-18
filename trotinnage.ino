#include "Wire.h"
#define Echo_InputPin 4
#define Trigger_OutputPin 5

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;
int Sensor = 2;
int val;
int maximumRange = 300;
int minimumRange = 2;

long Distance;
long Duration1;
double x;double y;double z;

void setup() 
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  pinMode (Sensor, INPUT) ;
  digitalWrite(Sensor, HIGH);

  pinMode(Trigger_OutputPin, OUTPUT);
  pinMode(Echo_InputPin, INPUT);
  
  Serial.begin(9600);
}

void loop() 
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
  if (z > 215 && z < 240)
      {
        Serial.println("tete de l'utilisateur proche du sol ou Choc");
        Serial.println("-----------------------------------------");
        }
  val = digitalRead (Sensor);
  if (val == LOW)
    {
      Serial.println("tete de l'utilisateur proche du sol ou Choc");
      }

  digitalWrite(Trigger_OutputPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigger_OutputPin, LOW);
  Duration1 = pulseIn(Echo_InputPin, HIGH);
  Distance = Duration1/58.2;
  if (Distance < 20)
  {
    Serial.println("La distance actuelle entre la tête et l'obstacle est de:");
    Serial.print(Distance);
    Serial.println("cm");
    Serial.println("-----------------------------------");
  }

}
