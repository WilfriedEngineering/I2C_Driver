#ifndef BUS_I2C_H
#define BUS_I2C_H

typedef struct{
    void (*Init)( unsigned long f_osc,const unsigned long f_bus);
    void (*Start)(void);
    void (*Repeated_Start)(void);
    char (*Write)(char x_data);
    char (*Read)(char ack_val);
    void (*Stop)(void);
}BUS_I2C;

    void BUS_I2C_Init( unsigned long f_osc,const unsigned long f_bus);
    void BUS_I2C_Start(void);
    void BUS_I2C_Repeated_Start(void);
    char BUS_I2C_Write(char x_data);
    char BUS_I2C_Read(char ack_val);
    void BUS_I2C_Stop(void);
#endif