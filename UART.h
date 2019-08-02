#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

/*fictitious Library for fictitious ARM*/
#include "simplARM.h"

#define MAX_BUFFER_SIZE             255

/*Range of length from 1 -> 255*/
#define LENGTH_OF_DATA_BYTES        1

#define POSITION_HANDLER_UART   (Uart.INTPOS)




/*creating global buffer*/
uint8_t buffer[MAX_BUFFER_SIZE]={0};

/*semaphore*/
     Semaphore Sem;


/*status of UART*//*
typedef enum UART_Status
{
    UART_IDLE,
    UART_WAIT_RESPONSE,
    UART_WAIT_ASKING
}Uart_Status;

//StATUS OF INTERRUPT
typedef enum INTERRUPT_STATUS
{
    IRQ_NONE,
    IRQ_RX_READY,
    IRQ_TX_READY
}Interrupt_Status;
*/
/*Data length from buffer or from buffer*/
typedef struct UART_Write_Buffer
{
    uint8_t Uart_Write_From_Buffer;
    uint8_t Uart_Write_To_Buffer;
}Uart_Buffer;

/*UART Registers 32 bits*/
typedef struct UART{
    uint32_t RX;
    uint32_t TX;
    uint32_t RX_READY;
    uint32_t TX_READY;
    uint32_t TX_INT;
    uint32_t RX_INT;
    uint32_t INTPOS;
}Uart;




/*standard data types*/
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;






/*API would be used*/
int UART_Init(void);
int UART_read(uint8_t *, int );
int UART_write(uint8_t *, int);

int Uart_Buffer_Init(void);

/*interrupts*/
void TX_Ready(void);
void RX_Ready(void);
#endif // UART_H_INCLUDED
