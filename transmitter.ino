#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>

//Defining Constants
const int x_out = A0;
const int y_out = A1;
RF24 radio(8, 10); // defining the pins at which RF24 is connected
const byte address[6] = "00001"; //Here we created a pipe with an address
//Making a Structure
struct data
{
  int xAxis;
  int yAxis;
};

data send_data;

void setup() 
{
  // put your setup code here, to run once:
  radio.begin();
  radio.openWritingPipe(address);// we open the pipe with parameter of address
  radio.setPALevel(RF24_PA_MIN);// Minimum power is defined here (For the RF24)
  radio.setDataRate(RF24_250KBPS);// Rate of transmission
  radio.stopListening();

}

void loop() 
{
  // put your main code here, to run repeatedly:
  send_data.xAxis = analogRead(x_out);
  send_data.yAxis = analogRead(y_out);
  radio.write(&send_data, sizeof(data));

}
