#include <Arduino.h>
#include <SPI.h>
#include "NRF24L01.h"

const int CE = 9;
const int CSN = 10;

void CS_select (void){
  digitalWrite(CSN, LOW);
}

void CS_unselect (void){
  digitalWrite(CSN, HIGH);
}

void CE_enable(void){
  digitalWrite(CE, HIGH);
}

void CE_disable(void){
  digitalWrite(CE, LOW);
}

void nrf24_WriteReg(uint8_t reg, uint8_t data){

  CS_select();
  SPI.transfer(reg|1<<5);
  SPI.transfer(data);
  CS_unselect();
}

void nrf24_WriteRegMulti(uint8_t reg, uint8_t *data, int size){
  CS_select();
  SPI.transfer(reg|1<<5);
  SPI.transfer(data, size);
  CS_unselect();
}

uint8_t nrf24_ReadReg(uint8_t reg){
  CS_select();
  SPI.transfer(reg);
  uint8_t data = SPI.transfer(0x00);
  CS_unselect();
  return data;
}

void nrf24_ReadReg_Multi (uint8_t reg, uint8_t *data, int size){
    CS_select();

    SPI.transfer(reg);
    SPI.transfer(data, size);

    CS_unselect();
}

void nrfsendcmd(uint8_t cmd){
  CS_select();
  SPI.transfer(cmd);
  CS_unselect();
}

void NRF24_Init(){
  CE_disable();

  nrf24_WriteReg(CONFIG, 0);
  nrf24_WriteReg(EN_AA, 0);
  nrf24_WriteReg(EN_RXADDR, 0);
  nrf24_WriteReg(SETUP_AW, 0x03);
  nrf24_WriteReg(SETUP_RETR, 0);
  nrf24_WriteReg(RF_CH, 0);
  nrf24_WriteReg(RF_SETUP, 0x0E);

  CE_enable();
}

void NRF24_TxMode(uint8_t *address, uint8_t channel){
    CE_disable();

    nrf24_WriteReg(RF_CH, channel);
    nrf24_WriteRegMulti(TX_ADDR, address, 5);
    
    uint8_t config = nrf24_ReadReg(CONFIG);
    config = config | (1<<1);
    nrf24_WriteReg(CONFIG, config);

    CE_enable();
}

uint8_t NRF24_Transmit (uint8_t *data){
    uint8_t cmdtosend = 0;
    CS_select();
    cmdtosend = W_TX_PAYLOAD;
    SPI.transfer(cmdtosend);
    SPI.transfer(data, 32);
    CS_unselect();
    delay(1);

    uint8_t fifostatus = nrf24_ReadReg(FIFO_STATUS);
    Serial.println(fifostatus);

    if ((fifostatus&(1<<4)) && !(fifostatus & (1<<3))){
        cmdtosend = FLUSH_TX;
        nrfsendcmd(cmdtosend);

        return 1;
    }

    return 0;
}

void NRF24_RxMode(uint8_t *address, uint8_t channel){
    CE_disable();

    nrf24_WriteReg(RF_CH, channel);
    uint8_t en_rxaddr = nrf24_ReadReg(EN_RXADDR);
    en_rxaddr |= (1<<1);
    nrf24_WriteReg(EN_RXADDR, en_rxaddr);
    nrf24_WriteRegMulti(RX_ADDR_P1, address, 5);

    nrf24_WriteReg(RX_PW_P1, 32);
    
    uint8_t config = nrf24_ReadReg(CONFIG);
    config |= (1<<1);
    config |= (1);
    nrf24_WriteReg(CONFIG, config);

    CE_enable();
}

uint8_t isDataAvailable (int pipenum){
    uint8_t status = nrf24_ReadReg(STATUS);
    if (status&(1<<6) && (status&(pipenum<<1))){
        nrf24_WriteReg(STATUS, (1<<6));
        return 1;
    }
    return 0;
}

void NRF24_Receive(uint8_t *data){
    uint8_t cmdtosend = 0;
    CS_select();
    cmdtosend = R_RX_PAYLOAD;
    SPI.transfer(cmdtosend);
    SPI.transfer(data, 32);
    CS_unselect();
    delay(1);

    cmdtosend = FLUSH_RX;
    nrfsendcmd(cmdtosend);
}