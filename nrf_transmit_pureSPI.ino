#include <SPI.h>

const int cs = 10;
const int ce = 9;
const int channel = 3;
const int addr = 0xB50000; //101101010000000000000000


void setup() {
  NRF_init();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void NRF_init(){
  pinMode(cs, OUTPUT);
  pinMode(ce, OUTPUT);
  digitalWrite(cs, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);

  // set PRIM_RX
  digitalWrite(cs, LOW);
  SPI.transfer(0x00&B00100000);
  SPI.transfer(0);
  digitalWrite(cs, HIGH);

  // set AW
  digitalWrite(cs, LOW);
  SPI.transfer(0x03&B00100000);
  SPI.transfer(B01000000);
  digitalWrite(cs, HIGH);

  // set TX_ADDR
  digitalWrite(cs, LOW);
  SPI.transfer(0x10&B00100000);
  SPI.transfer(addr); 
  digitalWrite(cs, HIGH);

  // set TX_PLD
  digitalWrite(cs, LOW);
  SPI.transfer(B10100000);
  SPI.transfer(0x2B2);
  digitalWrite(cs, HIGH);

  // transmit
  digitalWrite(ce, HIGH);
  delayMicroseconds(5);
  digitalWrite(ce, LOW);
}