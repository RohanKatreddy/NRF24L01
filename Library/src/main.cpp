// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(8, 9); // CE, CSN

// const byte address[6] = "00001";

// void setup() {
//   Serial.begin(9600);
//   radio.begin();
//   radio.openReadingPipe(0, address);
//   radio.setPALevel(RF24_PA_MAX);
//   radio.startListening();
// }

// void loop() {
//   if (radio.available()) {
//     char text[32] = "";
//     radio.read(&text, sizeof(text));
//     Serial.println(text);
//   }
// }

// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>

// RF24 radio(7, 8); // CE, CSN

// const byte address[6] = "00001";

// void setup() {
//   radio.begin();
//   radio.openWritingPipe(address);
//   radio.setPALevel(RF24_PA_MAX);
//   radio.stopListening();
// }

// void loop() {
//   const char text[] = "Hello World";
//   radio.write(&text, sizeof(text));
//   delay(1000);
// }

#include <Arduino.h>
#include <SPI.h>
#include "NRF24L01.h"

const int CE = 9;
const int CSN = 10;

uint8_t TxAddress[] = {0xEE, 0xDD, 0xCC, 0xBB, 0xAA};
uint8_t TxData[] = "Hello World\n";

void setup() {
  Serial.begin(115200);
  pinMode(CE, OUTPUT);
  pinMode(CSN, OUTPUT);
  pinMode(13, OUTPUT);
  SPI.begin();
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  NRF24_Init();
  NRF24_TxMode(TxAddress, 10);
}

void loop() {
  if (NRF24_Transmit(TxData) == 1){
    digitalWrite(13, HIGH);
    Serial.println("success");
  }
  else{
    digitalWrite(13, LOW);
    Serial.println("transmission failed");
  }

  delay(1000);
}