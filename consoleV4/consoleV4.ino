// Exam no: 116747 ENGINEERING HL PROJ 2022: CONSOLE CODE


//Wireless Setup
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
const byte address[6] = "00001";

//Data sent
int potPinS = A0;  // analog pin used to connect the servo potentiometer
int potPinM = A1;  // analog pin used to connect the motor potentiometer

char charBuf[12];
void setup() {

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

   Serial.begin(9600); //initialize serial communication at 9600 bits per second

  //Wireless Setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
//  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();


}
 
void loop() {
  int potValueS; // Servo val
  int potValueM; // Motor val
  potValueS = analogRead(potPinS);  // analog pin used to connect the Servo potentiometer
  potValueM = analogRead(potPinM);  // analog pin used to connect the motor potentiometer

//   Serial.print("S val: ");
//   Serial.println(potValueS);
//   Serial.print("M val: "); 
//   Serial.println(potValueM); 
//   
   String valS = String(potValueS); //converts Servo pot reading to string
   valS += "S";
   String valM = String(potValueM); // convert Motor Pot reading to string
   valM += "M";
   
   String sendVal = valS + valM;

   Serial.println(sendVal); // replace var for testing: valM

   sendVal.toCharArray(charBuf, 12);
   radio.write(&charBuf, sizeof(charBuf));
 

  delay(15);                           // waits for the servo to get there
}
