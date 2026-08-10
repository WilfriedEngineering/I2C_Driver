#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "BUS_I2C.h"

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 20000000 


BUS_I2C pbus={BUS_I2C_Init,BUS_I2C_Start,BUS_I2C_Repeated_Start,BUS_I2C_Write,BUS_I2C_Read, BUS_I2C_Stop}; // Defining of functions operating on the I2C bus
const char FIXED_ADDR= 0x70;

// x_addr= 0b0000XXX0 with x={0,1}
void Pca_Config(char x_val,char x_addr){
    pbus.Start();
    pbus.Write(0x70|x_addr); // writes device Address + writing operation
    pbus.Write(0x03);  // configuration register selecting '0' as output and '1' as input
    pbus.Write(x_val); // configuration values
    pbus.Stop();
}

void Pca_Write(char x_val,char x_addr){
    pbus.Start();
    pbus.Write(0x70|x_addr); // writes device Address + writing operation
    pbus.Write(0x01);      //  output register selecting 
    pbus.Write(x_val);    // writes values
    pbus.Stop();
}

unsigned char Pca_Read(char x_addr){
    unsigned char x_val;
    pbus.Start();
     pbus.Write(0x70|x_addr); // writes device Address + writing operation
    pbus.Write(0x00);     // input register selecting
    pbus.Repeated_Start();
    pbus.Write(0x71|x_addr); // writes device Address + reading operation
    x_val=pbus.Read(0);  // Read
    pbus.Stop();
    return x_val;
}

int main(int argc, char** argv) {
    char my_addr=0x0e;
    pbus.Init(20000000,100000); // initialize the clock frequency of the bus of 100KHz
    Pca_Config(0x0f,my_addr);
    Pca_Write(0x00, my_addr);
    while(1){
        Pca_Write((char)(Pca_Read(my_addr)<<4) , my_addr);
        __delay_ms(1000);
    
    }
    
    return (EXIT_SUCCESS);
}

