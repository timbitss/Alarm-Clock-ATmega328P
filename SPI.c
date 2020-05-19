#include "SPI.h"

void SPI_MasterInit(void)
{

    /* Set MOSI, SCK, and Slave Select as output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<SS);
    /* Start off with slave deselected high, enable internal pullup on MISO pin */
    SPIPORT |= ((1<<SS) | (1<<DD_MISO)); 
    
    /* Enable SPI, Master, set clock rate fck/64 */ 
    SPCR = ((1<<SPE)|(1<<MSTR)|(1<<SPR1));

}


uint8_t SPI_MasterTransmitReceive(unsigned char cData)
{

    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
    /* return received byte */
    return SPDR;

}





