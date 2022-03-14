/*
  Connection nRF4L01
  GND - GND
  VCC - 3V3
  CE - D8
  CNS - D9
  SCK - D13
  MOSI - D11
  MISO - D12
  SS - 10
*/

// H-Bridge Configuration

#include <SparkFun_TB6612.h>

#define pwmA 5
#define Ain1 2
#define Ain2 3
#define STBY A7
#define pwmB 6
#define Bin1 4
#define Bin2 7


const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(Ain1, Ain2, pwmA, offsetA, STBY);
Motor motor2 = Motor(Bin1, Bin2, pwmB, offsetB, STBY);

// nRF24L01 configuration

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>





const byte address[6] = "00001";

RF24 radio(8,9); //CE, CSN

struct Data_Package {
  int a=1;
  int s=1;
  int b=1;
  
  };
Data_Package data;


void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  
} 

void loop()
{
  delay(5);
  radio.startListening();
  if (radio.available()){
    
    radio.read(&data, sizeof(Data_Package));
    if(data.b ==3){
    motor1.drive(255,1000);
    motor2.drive(222,1000);
  }
  if(data.b==1){
    motor1.brake();
    motor2.brake();
  }
  Serial.print(data.a);
      Serial.print("  ");
      Serial.print(data.s);
      Serial.print("  ");
      Serial.println(data.b);
    }
  
  delay(5);
  radio.stopListening();
}
