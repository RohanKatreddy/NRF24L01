// // TRANSMIT CODE

// #include <Arduino.h>
// #include <SPI.h>
// #include "NRF24L01.h"

// const int CE = 9;
// const int CSN = 10;

// uint8_t TxAddress[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
// uint8_t TxData[] = "Hello World\n";

// void setup() {
//   Serial.begin(115200);
//   pinMode(CE, OUTPUT);
//   pinMode(CSN, OUTPUT);
//   pinMode(13, OUTPUT);
//   SPI.begin();
//   SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
//   NRF24_Init();
//   NRF24_TxMode(TxAddress, 10);
//   digitalWrite(CSN, LOW);
//   SPI.transfer(0x00);
//   SPI.transfer(2);
//   digitalWrite(CSN, HIGH);
// }

// void loop() {
//   // TESTING CODE FOR TRANSMIT
//   // digitalWrite(CE, LOW);
  
//   // digitalWrite(CSN, LOW);
//   // SPI.transfer(B10100000);
//   // SPI.transfer(69);
//   // digitalWrite(CSN, HIGH);


//   // digitalWrite(CSN, LOW);
//   // SPI.transfer(0x17);
//   // uint8_t data = SPI.transfer(0x00);
//   // digitalWrite(CSN, HIGH);
//   // Serial.println(data);

//   // digitalWrite(CE, HIGH);
//   // delay(10);

//   // digitalWrite(CSN, LOW);
//   // SPI.transfer(0x17);
//   // data = SPI.transfer(0x00);
//   // digitalWrite(CSN, HIGH);
//   // Serial.println(data);

//   // digitalWrite(CE, LOW);
//   // delay(5000);

//   if (NRF24_Transmit(TxData) == 1){
//     digitalWrite(13, HIGH);
//     Serial.println("success");
//   }
//   else{
//     digitalWrite(13, LOW);
//     Serial.println("transmission failed");
//   }

//   delay(1000);
// }



// RECIEVE CODE

#include <Arduino.h>
#include <SPI.h>
#include "NRF24L01.h"

const int CE = 9;
const int CSN = 10;

uint8_t RxAddress[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
uint8_t RxData[32];

void setup() {
  Serial.begin(115200);
  pinMode(CE, OUTPUT);
  pinMode(CSN, OUTPUT);
  pinMode(13, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  NRF24_Init();
  NRF24_RxMode(RxAddress, 10);
}

void loop() {
  if (isDataAvailable(1) == 1){
    NRF24_Receive(RxData);
    String out = "";
    for (int i = 0; i < 32; i++){
      out += char(RxData[i]);
    }
    Serial.print(out);
  }
}