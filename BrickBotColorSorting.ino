
/* This code works with GY-31 TCS3200 TCS230 color sensor module
*  It select a photodiode set and read its value (Red Set/Blue set/Green set) and displays  it on the Serial monitor
* and identify if possible the color
* Refer to  www.surtrtech.com for more details
*/
#include <Servo.h>

#define s0 8  //Module pins  wiring
#define s1 9
#define s2 10
#define s3 11
#define out 12


Servo servo1;
int servo1Pin = 13; //for turning the tube after color is detected
int solPin = 7; //for opening the trapdoor after color is determined



int Red = 0, Blue = 0, Green = 0;  //RGB values




void setup() {
 pinMode(s0, OUTPUT);  //pin modes
 pinMode(s1, OUTPUT);
 pinMode(s2, OUTPUT);
 pinMode(s3, OUTPUT);
 pinMode(out, INPUT);



 servo1.attach(servo1Pin);
 servo1.write(90);
 pinMode(solPin, OUTPUT);


 Serial.begin(9600);  //intialize the serial monitor  baud rate


 digitalWrite(s0, HIGH);  //Putting S0/S1 on HIGH/HIGH levels  means the output frequency scalling is at 100% (recommended)
 digitalWrite(s1, HIGH);  //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
 Serial.println("Starting");
delay(1000);
}




void loop() {

   servo1.write(90);



  GetColors();  //Execute the GetColors function  to get the value of each RGB color
               //Depending  of the RGB values given by the sensor we can define the color and displays it on  the monitor




 if (Red <= 15 && Green <= 15 && Blue <= 15) {  //If the values  are low it's likely the white color (all the colors are present)
   Serial.println("White");


 } else if (Red < Blue && Red <= Green && Red < 30) {  //if  Red value is the lowest one and smaller thant 23 it's likely Red
   servo1.write(90);
    Serial.println("Red - Servo @90");

   delay(200);
   digitalWrite(solPin, HIGH);
   delay(1000); 
   digitalWrite(solPin, LOW);
  servo1.write(90);
  Serial.println("After Red - Servo @90");




 } else if (Blue < Green && Blue < Red && Blue < 40) {  //Same thing for Blue
   servo1.write(63);
   Serial.println("Blue - Servo @90");

   delay(200);
   digitalWrite(solPin, HIGH);
   delay(1000); 
   digitalWrite(solPin, LOW);
   servo1.write(90);
  Serial.println("After Blue - Servo @90");


 } else if (Green < Red && Green - Blue <= 5) {  //Green it was a little tricky,  you can do it using the same method as above (the lowest), but here I used a reflective  object
   servo1.write(123);
   Serial.println("Green - Servo @123");

   delay(200);
   digitalWrite(solPin, HIGH);
   delay(1000); 
   digitalWrite(solPin, LOW);
  servo1.write(90);
  Serial.println("After Green - Servo @90");



 } else {
   Serial.println("Unknown - Servo @90");  //if the color is not recognized, you can add as many as you want
 }

   delay(5000);


}








void GetColors() {
 digitalWrite(s2, LOW);  //S2/S3 levels define which set  of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH  is for green
 digitalWrite(s3, LOW);
 Red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  //here we wait  until "out" go LOW, we start measuring the duration and stops when "out" is  HIGH again, if you have trouble with this expression check the bottom of the code
 delay(20);
 digitalWrite(s3, HIGH);  //Here  we select the other color (set of photodiodes) and measure the other colors value  using the same techinque
 Blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
 delay(20);
 digitalWrite(s2, HIGH);
 Green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
 delay(20);
}




//Here's an  example how to understand that expression above,
//""digitalRead(out) == HIGH  ? LOW : HIGH"" this whole expression is either HIGH or LOW as pulseIn function  requires a HIGH/LOW value on the second argument




//led_Status = led_Status  == HIGH ? LOW : HIGH;
//
//if(led_Status == HIGH)
//{
//led_Status  =LOW;
//}
//else
//{
//led_Status = HIGH;
//}


