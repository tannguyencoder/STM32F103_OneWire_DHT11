#include "I2C.h"

uint8_t receivedByte;

I2C_InitTypeDef i2cInit;
GPIO_InitTypeDef i2cGPIO;
void i2c_init(void){
	//Initialize I2C
	RCC_APB1PeriphClockCmd(I2Cx_RCC, ENABLE);
	i2cInit.I2C_ClockSpeed=100000;
	i2cInit.I2C_Mode = I2C_Mode_I2C;
	i2cInit.I2C_DutyCycle=I2C_DutyCycle_2;
	i2cInit.I2C_Ack=I2C_Ack_Disable;
	i2cInit.I2C_OwnAddress1=0;
	i2cInit.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2Cx,&i2cInit);
	I2C_Cmd(I2Cx,ENABLE);
	//Initialize GPIO as open drain alternate funtion
	RCC_APB2PeriphClockCmd(I2C_GPIO_RCC, ENABLE);
	i2cGPIO.GPIO_Pin = I2C_PIN_SCL | I2C_PIN_SDA;
	i2cGPIO.GPIO_Mode = GPIO_Mode_AF_OD;
	i2cGPIO.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(I2C_GPIO, &i2cGPIO);
	
}
void i2c_start(void){
	//Wait until I2Cx is not busy anymore 
	while (I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY));
	//Generate start condition
	I2C_GenerateSTART(I2Cx,ENABLE);
	//Check no other devices is communicating
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));
	
}
void i2c_stop(void){
	//Generate stop condition
	I2C_GenerateSTOP(I2Cx, ENABLE);
	//Wait util I2C stop condition is finished
	while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF));
}
void i2c_address_direction(uint8_t address, uint8_t direction){
	I2C_Send7bitAddress(I2Cx,address,direction);
	//Wait for A slave acknowledges his address
	if (direction == I2C_Direction_Transmitter)
    {
        while (!I2C_CheckEvent(I2Cx,
            I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    }
    else if (direction == I2C_Direction_Receiver)
    { 
        while (!I2C_CheckEvent(I2Cx,
            I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    }
}
void i2c_transmit(uint8_t byte){
	I2C_SendData(I2Cx,byte);
	//Wait for data has been shifted out and output on the bus
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}
uint8_t i2c_receive_ack(void){
	//Enable ACK of received data
	I2C_AcknowledgeConfig(I2Cx, ENABLE);
	//Wait for data has been received in I2C data register
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	//Read and return data byte form I2C data register
	return I2C_ReceiveData(I2Cx);
}
uint8_t i2c_receive_nack(void){
	// Disable ACK of received data
  I2C_AcknowledgeConfig(I2Cx, DISABLE);
	//Wait for data has been received in I2C data register
	while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));
	// Read and return data byte from I2C data register
	return I2C_ReceiveData(I2Cx);
}
void i2c_write(uint8_t address, uint8_t data){
		i2c_start();
    i2c_address_direction(address << 1, I2C_Direction_Transmitter);
    i2c_transmit(data);
    i2c_stop();
}
void i2c_read(uint8_t address, uint8_t* data){
		i2c_start();
    i2c_address_direction(address << 1, I2C_Direction_Receiver);
    *data = i2c_receive_nack();
    i2c_stop();
}