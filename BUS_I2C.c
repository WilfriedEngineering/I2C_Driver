#include <xc.h>

#include "BUS_I2C.h"

/*
    Here you can write your function if they are not create
    else 
*/


    void BUS_I2C_Init( unsigned long f_osc,const unsigned long f_bus){
        SSPCONbits.SSPEN=1;
        SSPCONbits.SSPM3=1;
        SSPCONbits.SSPM2=0;
        SSPCONbits.SSPM1=0;
        SSPCONbits.SSPM0=0;
        SSPSTAT=0x80;
        f_osc= f_osc/(4*f_bus)-1;
        SSPADD= (char)(f_osc);
             
    }
    
    void BUS_I2C_Start(void){ 
           SSPCON2bits.SEN=1;
           while(SSPCON2bits.SEN); 
    }
    
    void BUS_I2C_Repeated_Start(void){
        SSPCON2bits.RSEN=1;
        while((!SSPSTATbits.S)||(!PIR1bits.SSPIF));     
    }
    
    char BUS_I2C_Write(char x_data){
       
       SSPBUF = x_data;
       PIR1bits.SSPIF=0;
       while((!PIR1bits.SSPIF));
      
       return SSPCON2bits.ACKSTAT;
       
        
       
    }
    
    char BUS_I2C_Read(char ack_val){
        char x_data;
        SSPCON2bits.RCEN=1;
        while(!SSPSTATbits.BF);       
        x_data=SSPBUF;
        while(SSPSTATbits.BF);
        if(!ack_val) SSPCON2bits.ACKDT=1;
        else SSPCON2bits.ACKDT=0;
        SSPCON2bits.ACKEN=1;
        while(SSPCON2bits.ACKEN);
        return x_data;
    }
    
    void BUS_I2C_Stop(void){
        SSPCON2bits.PEN=1;
        while(SSPCON2bits.PEN);
        
    }




