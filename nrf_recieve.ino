#include <SPI.h>

const int cs = 10;
const int ce = 9;
const int channel = 3;
const int addr = 0xB50000l; //101101010000000000000000


void setup() {
  Serial.begin(115200);
  NRF_init();
}

void loop() {
  digitalWrite(cs, LOW);
  SPI.transfer(0x07);
  byte n = SPI.transfer(0x00);
  digitalWrite(cs, HIGH);

  Serial.println(n);
  
  if (n && 00000010){
  digitalWrite(ce, LOW);
  digitalWrite(cs, LOW);
  SPI.transfer(B01100001);
  unsigned int i = SPI.transfer(0x00);
  digitalWrite(cs, HIGH);
  Serial.println(i);}
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
  SPI.transfer(1);
  digitalWrite(cs, HIGH);

  // set EN_RXADDR
  digitalWrite(cs, LOW);
  SPI.transfer(0x02&B00100000);
  SPI.transfer(B11111100);

  // set AW
  digitalWrite(cs, LOW);
  SPI.transfer(0x03&B00100000);
  SPI.transfer(B01000000);
  digitalWrite(cs, HIGH);

  // set RX_ADDR_P0
  digitalWrite(cs, LOW);
  SPI.transfer(0x0A&B00100000);
  SPI.transfer(addr); 
  digitalWrite(cs, HIGH);

  // recieve
  digitalWrite(ce, HIGH);

  
  
}