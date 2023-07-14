#include<Servo.h>
// defines pins numbers
const int trigPin = 9;
const int echoPin = 11;
const int servo_pin=3;
//12.2
const int rightl=4;
const int righth=5;
const int leftH=6;
const int leftl=7;


double pingtime;
double distance;
int servopos=90;
int angle;
Servo myServo;

////////

/////////


void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

 
  //Motor initialiazation
  pinMode(righth,OUTPUT);
  pinMode(leftH,OUTPUT);
  pinMode(rightl,OUTPUT);
  pinMode(leftl,OUTPUT);

 
  //Servo initialization
  myServo.attach(servo_pin);
  Serial.begin(9600); // Starts the serial communication
 
  }

void turn(int angle)
{
   
   
  if(angle<90)        //right
   {
   
     digitalWrite(leftH,HIGH);
     digitalWrite(righth,LOW);
     digitalWrite(rightl,HIGH);
     digitalWrite(leftl,LOW);
     delay((90-angle)*13);
   
   }  
   else if (angle>=90)    //left
   {
     //for(int i=0;i<=(angle-90)*1000;i++)
     //{
     digitalWrite(leftH,LOW);
     digitalWrite(righth,HIGH);
     digitalWrite(rightl,LOW);
     digitalWrite(leftl,HIGH);
     //}
     delay((angle-90)*13);
   }

 }

double sensor()
{
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  pingtime=pulseIn(echoPin,HIGH);
  delay(10);
  distance=pingtime*0.034/2;
  return distance;
  }
 
int rotate()
{
  //Serial.println("i am here");
  int max_distance=0;
  int current_distance=0;
  int angle=0;
  int pingtime=0;
  for(int i=0;i<180;i=i+15)
  {
      myServo.write(i);
    current_distance=sensor();
    if(max_distance<=current_distance)
    {
      max_distance=current_distance;
      angle=i;
    }
    delay(50);
   }  
   if(max_distance<35)
   return 180;
   if(angle>90)
   return (angle+10);
   else
   return (angle-10);
}

void loop()
{
 
 
  myServo.write(90);
     digitalWrite(leftH,HIGH);
     digitalWrite(righth,HIGH);
     digitalWrite(rightl,LOW);
     digitalWrite(leftl,LOW);
  distance=sensor();
  if(distance<=25)
  {

   digitalWrite(leftH,LOW);
   digitalWrite(righth,LOW);
   digitalWrite(rightl,LOW);
   digitalWrite(leftl,LOW);
   angle=rotate();
   delay(100);
   turn(angle);
   Serial.println("angle is");
   Serial.println(angle);
   
     digitalWrite(leftH,HIGH);
     digitalWrite(righth,HIGH);
     digitalWrite(rightl,LOW);
     digitalWrite(leftl,LOW);
   myServo.write(90);    
   
  }
 
 
}
