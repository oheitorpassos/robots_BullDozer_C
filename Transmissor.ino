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


/* 
  Connection HC-06
  GND - GND
  VCC - 5V
  TX  - D2
  RX  - D3 3V3 Voltage Divider
*/


// HC-06 configuration

#include <SoftwareSerial.h>

SoftwareSerial bluetooth(2,3);

// Create String to receive Bluetooth Data
String value;


// nRF24L01 configuration

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(8,9);

//Endereço do módulo

const byte address[6] = "00001";


void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600);
  // Setup Bluetooth Communication
  bluetooth.begin(9600);
  // Setup Radio Communication
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  
  
}

void loop()
{
  // Receive Bluetooth data from Arduino Joystick Android app
  if(bluetooth.available()>0){
    value = bluetooth.readStringUntil('#');
    if (value.length()==7){
      //Creates Data Package
      struct Data_Package {
      int a = value.substring(0,3).toInt(); 
      int s = value.substring(3,6).toInt();
      int b = value.substring(6,8).toInt();
      };
      
      Data_Package data;
  
      
      //Serial.flush();

      
      // Sends datapackage to Radio
      radio.write(&data, sizeof(Data_Package));
      delay(500);
      // resets bluetooth data String 
      value="";
      
    }
  }
}
