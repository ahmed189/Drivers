#include "UART.h"

//make instance from data type
struct UART_Write_Buffer Uart_Buffer;

//prototype of static function
static int Uart_Buffer_Init(void);

//There is global Structure Called Uart
//end



int UART_Init(void)
{
    //Disables global interrupts and begins a critical section
    void OSLock();
    /*
        configuration of registers:
        - Configuration PINS to use as TX and RX not GPIOS if valid
        - Enable Clock
        - Sample mode
        - Number of data bits
        - specify number of stop bits
        - specify parity check configuration
        - Baudrate
        - Enable uart
        - Enable Transmitter and Receiver
        - Enable interrupts we need
    */
        Uart.TX_INT = 1;
        Uart.RX_INT = 1;

    /*initialize interrupts handlers*/
    simpl_install_handler(POSITION_HANDLER_UART,&Uart_Handler);

    Uart_Buffer_Init();

    /*Create semaphore*/
    Sem = OSCreateSemaphore(1);
    Sync_Sem_tx = OSCreateSemaphore(0);
    Sync_Sem_rx = OSCreateSemaphore(0);


    //Enable global interrupts and Finish a critical section
    void OSUnlock();
    //for debugging
    return 1;
}
void Uart_Handler(void)
{
    const uint8_t var = (uint8_t)0x01;
    if( (var & UART.RX_READY) = (uint8_t)0x01)
    {
        OSSemaphoreSignal(Sync_Sem_rx);
    }
    else;
    if( (var & UART.TX_READY) = (uint8_t)0x01)
    {
        OSSemaphoreSignal(Sync_Sem_tx);
    }
    else;
}
void TX_Ready(void)
{
    //Atomically decrease the semaphore value by 1. If the value is negative, suspends the calling thread.
    //used for synchronization
    OSSemaphoreWait(Sync_Sem_tx);

    //Protection from mutual exclusion by entering critical section
    OSSemaphoreWait(Sem);

    if(UART_write(&buffer , LENGTH_OF_DATA_BYTES) == 0)
        /*error handling mode*/
    else;

    //Atomically increments the semaphore value by 1. If the value is non positive, wakes up a suspended thread
    //Release semaphore to end critical section
    OSSemaphoreSignal(Sem);

}
void RX_Ready(void)
{
    //Atomically decrease the semaphore value by 1. If the value is negative, suspends the calling thread.
    //used for synchronization
    OSSemaphoreWait(Sync_Sem_rx);

    //Protection from mutual exclusion by entering critical section
    OSSemaphoreWait(Sem);

    if(UART_read(&buffer , LENGTH_OF_DATA_BYTES) == 0)
        /*error handling mode*/
    else;

    //Atomically increments the semaphore value by 1. If the value is non positive, wakes up a suspended thread
    //Release semaphore to end critical section
    OSSemaphoreSignal(Sem);
}



int UART_read(uint8_t *buffer, int len)
{
    static uint8_t index_R = 0;
    //check size of read buffer
    if(len < MAX_BUFFER_SIZE)
    {
        index_R++;

        //check size of the data read
        if(index_R > len)
        {
            Uart_Buffer.Uart_Write_To_Buffer = 0;
            index_R = 1;
        }
        else;

        //save data from rx
        *(buffer + Uart_Buffer.Uart_Write_To_Buffer) = Uart.RX;
        Uart_Buffer.Uart_Write_To_Buffer++;
    }
    else
    {
        return 0;
    }
    return 1;
}





int UART_write(uint8_t *buffer, int len)
{
    static uint8_t index_W = 0;
    //check size of read buffer
    if(len < MAX_BUFFER_SIZE)
    {
        index_W++;

        //check size of the data read
        if(index_W > len)
        {
            Uart_Buffer.Uart_Write_From_Buffer = 0;
            index_W = 1;
        }
        else;

        //put data to send
        Uart.TX = *(buffer + Uart_Buffer.Uart_Write_From_Buffer);
        Uart_Buffer.Uart_Write_From_Buffer++;
    }
    else
    {
        return 0;
    }
    return 1;

}




static int Uart_Buffer_Init(void)
{
    Uart_Buffer.Uart_Write_From_Buffer = 0;
    Uart_Buffer.Uart_Write_To_Buffer   = 0;
}
