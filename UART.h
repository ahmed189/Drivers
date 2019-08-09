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
     Semaphore Sync_Sem_tx;
     Semaphore Sync_Sem_rx;



/*Data length from buffer or to buffer*/
typedef struct UART_Write_Buffer
{
    uint8_t Uart_Write_From_Buffer;
    uint8_t Uart_Write_To_Buffer;
};






/*standard data types*/
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;



/*API would be used*/
int UART_Init(void);
int UART_read(uint8_t *, int );
int UART_write(uint8_t *, int);


/*interrupts*/
void TX_Ready(void);
void RX_Ready(void);
#endif // UART_H_INCLUDED
