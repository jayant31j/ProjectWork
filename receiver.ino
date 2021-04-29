#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

const byte address[6] = "00001"; //Here we created a pipe address required to connect 2 nrf modules

int ENA = 3;//for turning the motors ON, OFF and control its speed
int ENB = 9;//for turning the motors ON, OFF and control its speed
int MotorA1 = 4;//for controlling motor A1
int MotorA2 = 5;//for controlling motor A2
int MotorB1 = 6;//for controlling motor B1
int MotorB2 = 7;//for controlling motor B2

RF24 radio(8, 10);

struct data 
{
  int xAxis;
  int yAxis;
};

data receive_data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);// Baud rate for the arduino (Serial monitor)
radio.begin();
radio.openReadingPipe(0,address);// for opening the pipe. 
radio.setPALevel(RF24_PA_MIN);// Minimum power consumption is defined for transmitting Data
radio.setDataRate(RF24_250KBPS);// defining the data receiving rate 
radio.startListening();
pinMode(ENA, OUTPUT);//for turning the motors ON, OFF and control its speed
pinMode(ENB, OUTPUT);//for turning the motors ON, OFF and control its speed
pinMode(MotorA1, OUTPUT);//for controlling motor A1
pinMode(MotorA2, OUTPUT);//for controlling motor A2
pinMode(MotorB1, OUTPUT);//for controlling motor B1
pinMode(MotorB2, OUTPUT);//for controlling motor B2

}

void loop() {
  // put your main code here, to run repeatedly:
  while(radio.available())//For defining motors HIGH and LOW
 {
  radio.read(&receive_data, sizeof(data));
   if(receive_data.yAxis > 400)
    {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);  
    }
   else if(receive_data.yAxis < 320) 
    {
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    } 
   else if(receive_data.xAxis < 320) 
    {
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    }
   else if(receive_data.xAxis > 400) 
    {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
    }
   else // for neutral position
    {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
    }
 }

}
