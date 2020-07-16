#ifndef __I2C_H
#define __I2C_H 			

#include "includes.h"

#define I2Cx_RCC        RCC_APB1Periph_I2C2
#define I2Cx            I2C2
#define I2C_GPIO_RCC    RCC_APB2Periph_GPIOB
#define I2C_GPIO        GPIOB
#define I2C_PIN_SDA     GPIO_Pin_7
#define I2C_PIN_SCL     GPIO_Pin_6

#define SLAVE_ADDRESS 0x08

void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_address_direction(uint8_t address, uint8_t direction);
void i2c_transmit(uint8_t byte);
uint8_t i2c_receive_ack(void);
uint8_t i2c_receive_nack(void);
void i2c_write(uint8_t address, uint8_t data);
void i2c_read(uint8_t address, uint8_t* data);


#endif