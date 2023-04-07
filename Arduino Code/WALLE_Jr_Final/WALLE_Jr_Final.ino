 /*
 * ENME 408 
 * Line Following Program 
 * Jonathan Shulgach
 * 10/4/15  
 * 
 * This code allows the robot to follow a line using a PID controller and calibration component 
 * to detect variances between light intensities of the surface. The code also allows the robot
 * to distinguish distances between objects the robot faces, and creates a sound when an object 
 * is detected in its path.
 * 
 * Credit to www.instructables.com for line following robot design project ideas and for code 
 * examples. Acknowledgements to Dr. Stephen Wilkerson for providing examples of photoresistor, 
 * LED, motor, and variable initialization code examples.
 */
 

//Initialize variables and libraries
#include <Servo.h> 
Servo Left;
Servo Right;

#define sensorLeft 15 //A1
#define sensorRight 14 //A0
#define trigPin 12
#define echoPin 11 
#define buzz 8
#define ledB 7 //Blue
#define ledY 6 //Yellow
#define btn 3 //button
#define ledG 2 //Green
#define ledR 4 //Red



const int sens2 = 14;
const int sens1 = 15;
int pos = 0; //initial conditions
int lightread[150];
int sensorValue1 = 0;
int sensorValue2 = 0; 
int sensorMax = 0;
int sensorMin = 1023;
int mid = 0;
int mybtn = 0;
int g_state = 0; 
int dx = 0;
int dxd = 0;
char RUN =0; 
int j = 0;
int k = 0;
int rlog = 0;
int llog = 0;


//Begin set up loop by setting pins to input and output modes
void setup() {
 Serial.begin(9600);
 pinMode(trigPin,OUTPUT);
 pinMode(echoPin,INPUT);
 pinMode(ledB,OUTPUT);
 pinMode(ledY,OUTPUT);
 pinMode(ledR,OUTPUT);
 pinMode(ledG,OUTPUT);
 pinMode(btn,INPUT_PULLUP);
 Right.attach(9, 800, 2200);
 Left.attach(10, 800, 2200);
}


  
//This is the main loop which allows the robot to run its line following and 
//pinging functions by pressing the button
void loop() 
{
 mybtn=digitalRead(btn);
 //Serial.print(mybtn); //These can be initialized during testing of the code to
 //Serial.print(",");
 //Serial.println(g_state);
 
 if((mybtn==0) && (g_state==0))
{
 g_state=1;
} 
else if((mybtn==0) && (g_state==1))
{
g_state=2;
}
else if((mybtn==0)&&(g_state==2))
{
g_state=0;  
}

 if (g_state==1)
 {
  digitalWrite(ledB,HIGH); //If button is pressed, line following program will execute
  linefollow(10);
  Serial.println(dx);
 }
 
 if (g_state==2) //If button is pressed, robot will enter into entertain mode with the lights acting in sequence
 {
  digitalWrite(ledR,HIGH);
  delay(50);
  digitalWrite(ledG,HIGH);
  delay(50);
  digitalWrite(ledY,HIGH);
  delay(50);
  digitalWrite(ledB,HIGH);
  delay(50);
  digitalWrite(ledR,LOW);
  delay(50);
  digitalWrite(ledG,LOW);
  delay(50);
  digitalWrite(ledY,LOW);
  delay(50);
  digitalWrite(ledB,LOW);
  delay(50); 
  j=0;
  k=0;
  Right.write(90);
  Left.write(90);
 }

 if (g_state==0) //If button is pressed, robot will enter standby mode with the yellow light flashing
 {
  digitalWrite(ledY,HIGH);
  delay(100);
  digitalWrite(ledY,LOW);
  delay(100);
  j=0;
  k=0;
 }
}
 


void linefollow(int del) //This is the line following function which tells the robot to follow a line for either a duration or until told to stop
{
 if (j<1)
 {
Serial.println("Calibrating max and min sensor values. Please cover photoresistor for a few seconds");
   k=0;
   while (k < 1000) {       //calibrate sensor to record max and min values for 1000 increments, around 10 seconds
    sensorValue1 = analogRead(sens1);  
    digitalWrite(ledB,HIGH);
      if (sensorValue1 > sensorMax) {
          sensorMax = sensorValue1;
      }  
      if (sensorValue1 < sensorMin) {
          sensorMin = sensorValue1; 
      }
      Serial.println(k);
      k=k+1;       
   }
   
   digitalWrite(ledB, LOW);
   mid = (sensorMax+sensorMin)/2;

   
 Serial.println(sensorMax); //All lights will flash once when calibration sequence is finished
 Serial.println(sensorMin);
 digitalWrite(ledG,HIGH);
 digitalWrite(ledR,HIGH);
 digitalWrite(ledY,HIGH);
 digitalWrite(ledB,HIGH);
 delay(1000);
 digitalWrite(ledG,LOW);
 digitalWrite(ledR,LOW);
 digitalWrite(ledY,LOW);
 digitalWrite(ledB,LOW);
 delay(1000);
 j=j+1;
}

  sensorValue1 = analogRead(sensorRight); //read port A0  
  int rightmapval = map(sensorValue1, sensorMin, sensorMax, 0, 100); //display sensor reading between 1 and 100
  rightmapval = constrain(sensorValue1, 0, 100);   
    
  sensorValue2 = analogRead(sensorLeft);
  int leftmapval = map(sensorValue2, sensorMin, sensorMax, 0, 100); //display sensor reading between 1 and 100
  leftmapval = constrain(sensorValue2 , 0, 100);
    
  Serial.print(rightmapval);
  Serial.print(" ");
  Serial.println(leftmapval);
  
  dx=(leftmapval-rightmapval); //This is the change in value between the sensors which controls the PID controller
  
if ((dx<=50) && (dx>=-50)) //If there's no significant difference in color, the robot will go forward.
{
  Right.write(0);
  Left.write(180);
  digitalWrite(ledB,LOW);
}

else if (dx>50) //controls right wheel power (smaller than -50 makes wheel go backward
{
  Right.write(0);
  llog=90 + (dx/3 + (dxd-dx)/5)-90;
  Serial.println(llog);  
  Left.write(llog);
  Right.write(0);
  digitalWrite(ledB,HIGH);
  dxd=dx;
  delay(50);
}
else if (dx<-50) //controlls left wheel power (greater than -20 makes wheel go backward
{ 
  Left.write(180);
  rlog=90 - (dx/3 + (dxd-dx)/5) + 10;
  Serial.println(rlog);
  Right.write(rlog);
  Left.write(180);
  digitalWrite(ledB,HIGH);
  dxd=dx;
  delay(50);
}
else
{ 
  Right.write(90); //Robot will stop for emergency
  Left.write(90); 
}
ping(10); //This runs the pinging subfunction which can be turned off here to decrease tthe latency of the line following function
}


void ping(int del) //This is the ultrasonic sensor function which tells the robot to buzz when a object comes within 10 cm from the robot.
{
  long duration, distance;
  digitalWrite(trigPin,LOW);
  delay(10);
  digitalWrite(trigPin,HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=(duration/2)/29.1; //Conversion from ultrasonic sensor values to centimeters
  if (distance<10) {
    digitalWrite(ledY,HIGH); //If objects out of range, green LED stays on
    digitalWrite(ledG,LOW);
    tone(buzz,800,100);
    delay(10);
  }
  else {
    digitalWrite(ledY,LOW); //If objects come within 10cm, yellow LED comes on.
    digitalWrite(ledG,HIGH);    
    delay(10);
  }
  if (distance>=300||distance<=0){
    //Serial.println("Out of range"); //This can be activated during the testing of the code
  }
  else{
    //Serial.print(distance); //display distance if necessary to test code
    //Serial.println(" cm");
  }
  
  delay(del);
}
