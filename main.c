#include "stm32f10x.h"
#include "osKernel.h"
#include "uart.h"
uint32_t semaphore1, semaphore2;
uint8_t cnt0;
uint8_t cnt1;
void Task0(void);
void Task1(void);

void MotorRun();
void MotorStop();
int main(void) {
    SystemClock72MHz()  ; // Optional if clock setup is needed
    UART1_Init();

    
		osKernelInit();
    osKernelAddThread(&Task0, &Task1);
		osSemaphore_Init(&semaphore1, 1);
		osSemaphore_Init(&semaphore2, 0);

    osKernelLaunch(1000); // Quanta in ms (example: 1000ms = 1 second)

    while (1); // Should never reach here
}


void Task0(){
	while(1){
		osCooperative_Wait(&semaphore1);
		cnt0++;
		MotorRun();
		for (volatile int i = 0; i < 100000; i++);
		osSemaphore_Give(&semaphore2);
	}
}
void Task1(){
	while(1){
		osCooperative_Wait(&semaphore2);
		cnt1++;
		MotorStop ();
		osSemaphore_Give(&semaphore1);
	}
}
void MotorRun(void) {
    // Your motor control logic here (e.g., GPIO on)
    UART1_SendString("Motor is running..\r\n");
		
}

void MotorStop(void) {
    // Your motor stop logic here (e.g., GPIO off)
		
    UART1_SendString("Motor has stopped.\r\n");
}