// Exam no: 116747 ENGINEERING HL PROJ 2022: CAR CODE

//curent version adds motor and led control

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Servo.h>  // add servo library
 
 Servo myservo;  // create servo object to control a servo

  int servoConv; // servo conversion
  char recivedVal[15]; //defining the buffer for the max possible length we can receive
  String convRecivedVal; // used for turing recivedVal into a string to make it easier to work with
  int motorSpeed = 0;
  int sVal; //servo value saved as int
  int mVal; //motor value saved as int



 // Tb6612 H-bridge setup
#define PWM1 3
#define AIN1 4
#define AIN2 5

int led = 2; //led on pin 2
  
  RF24 radio(7,8);

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600); //initialize serial communication at 9600 bits per second
  myservo.attach(6);  // attaches the servo on pin 10 to the servo object
  
  // Wireless setup
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
//  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

  // Motor Control Setup
  pinMode(PWM1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);

 pinMode(led, OUTPUT);

}

void loop() {

  // Recives and stores data from console
  if (radio.available()) {
    
    radio.read(&recivedVal, sizeof(recivedVal));
    String convRecivedVal = String(recivedVal);  // turns received byte array into a useable string
    Serial.println("rawStr:"+convRecivedVal);
    int posOfS = convRecivedVal.indexOf('S'); // number :stored value of the postition of s in the string 
    
    String servoVal = convRecivedVal.substring(0,posOfS); // first half of string containing servo values
    String MotorVal = convRecivedVal.substring(posOfS +1, convRecivedVal.indexOf('M'));  // second half of string containing motor values

    
   sVal = (int)servoVal.toInt(); //servo value now int
   mVal = (int)MotorVal.toInt(); //motor value now int

  }
//   Serial.print("rec:");
//   Serial.print(sVal);
//    Serial.print(" mval:");
//   Serial.print(mVal);
//   Serial.println("");

    motorSpeed =  map(mVal, 0, 1020, 0, 200  ); //determins speed 

    Serial.print("motor speed");
    Serial.println(motorSpeed);

    digitalWrite(AIN1,HIGH); //Motor Rotate Clockwise
    digitalWrite(AIN2,LOW);

    analogWrite(PWM1,motorSpeed); //Speed control of Motor 

    if(motorSpeed == 0){
     digitalWrite(led, LOW); //set led off

      }else{
        digitalWrite(led, HIGH); //set led off
      }
          
//    if(mVal <= 300){
//      // Sets if motor is forward, reverse or off
//      digitalWrite(AIN1,HIGH); //Motor A Rotate Clockwise
//      digitalWrite(AIN2,LOW);
//
//      digitalWrite(led, HIGH);
//      
//      motorSpeed =  map(mVal, 0, 300, 0, 150); //determins speed 
//    }else if(mVal <= 600) {
//        // Sets if motor is off
//        digitalWrite(AIN1,LOW); //Motor A off
//        digitalWrite(AIN2,LOW);
//
//        digitalWrite(led, LOW);
//
//
//      motorSpeed =  map(mVal, 300, 600, 0, 0); //determins speed 
//    }else {
//      digitalWrite(AIN1,LOW); //Motor A Rotate antiClockwise
//      digitalWrite(AIN2,HIGH  );
//
//      digitalWrite(led, LOW);
//      
//      motorSpeed =  map(mVal, 600, 1023, 0, 150); //determins speed 
//    }
//      
//
  



   

    
    servoConv = map(sVal, 0, 1023, 0, 175);     // scale it to use it with the servo (value between 0 and 180)
    myservo.write(servoConv);                  // sets the servo position according to the scaled value
         
   
    delay(15);                           // waits for the servo to get there
X}
