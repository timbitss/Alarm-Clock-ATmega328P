
#ifndef SPI_H
#define SPI_H

#ifndef DDR_SPI
#define DDR_SPI DDRB
#endif

#ifndef DD_MOSI
#define DD_MOSI PB3
#endif

#ifndef DD_SCK
#define DD_SCK PB5
#endif

#ifndef DD_MISO
#define DD_MISO PB4
#endif

#ifndef SS
#define SS PB2
#endif

#ifndef SPIPORT
#define SPIPORT PORTB
#endif

#define TEMPSTARTBYTE 0b00000001
#define TEMPSELCHANNEL0  0b10000000

#define SPI_StartTransmission SPIPORT &= ~(1<<SS) //SS pulled low to start transmission
#define SPI_EndTransmission   SPIPORT |= (1<<SS); //SS pulled high to end transmission

#include <avr/io.h>
#include <stdint.h>


void SPI_MasterInit(void); //initializes SPI

uint8_t SPI_MasterTransmitReceive(unsigned char cData); //send and receive data


#endif