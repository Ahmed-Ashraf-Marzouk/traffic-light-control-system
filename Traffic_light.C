// Include used libraries
#include "Traffic_light.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.c"
#include "driverlib/timer.h"
#include "tm4c123gh6pm.h"

// Global variables used in the main.c defined as extern 
extern int_32 next_state;
extern int_32 next_state_2;
extern int_32 next_state_ps;
extern int_32 ps_1;
extern int_32 ps_2;
extern int_32 elapsed_time_1;
extern int_32 elapsed_time_2;


// function handles the traffic light 1 interrupt
void Timer0_handler() 
{
  TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //CLEAR THE FLAG 
  switch(next_state)
  {
  case GREEN_1:
	  Timer0_init(5-Ticks_to_time(elapsed_time_1));
	  elapsed_time_1 = 0;
	  next_state = YELLOW_1; // blue
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // RED_ps_1
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0); // GREEN_ps_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0); // RED_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4); // GREEN_1
	  break; 
  case YELLOW_1: 
	  Timer0_init(2);
	  next_state = RED_1;
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0); // GREEN_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3); // YELLOW_1
	  break; 
  case RED_1:
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0); // YELLOW_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0); // GREEN_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2); // RED_1
	  next_state_2 = GREEN_2;
	  Timer0_dsiable();	
	  Timer1_init(1); 
	  break;	
  case GREEN_ps_1:
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0); // YELLOW_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0); // GREEN_1
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2); // RED_1
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0); // RED_ps_1
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4); // GREEN_ps_1
	  Timer0_init(2); 
	  next_state = RED_ps_1; 
	break;
  case RED_ps_1:
	  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0); // YELLOW_1
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // RED_ps_1
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0); // GREEN_ps_1
	  next_state = GREEN_1;
	  reset_traffic_2();
	  Timer0_init(1); 

	break; 
	}
}

// function handles the traffic light 2 interrupt
void Timer1_handler()
{
  TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT); //CLEAR THE FLAG 
  switch(next_state_2)
  {
  case GREEN_2:
	  Timer1_init(5 - Ticks_to_time(elapsed_time_2));
	  elapsed_time_2 = 0; 
	  next_state_2 = YELLOW_2;
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2); // RED_ps_2
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0); // GREEN_ps_2
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0); // RED_2
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PIN_0); // GREEN_2
	  break; 
  case YELLOW_2: 
	  Timer1_init(2);
	  next_state_2 = RED_2;
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0); // GREEN_2
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2); // YELLOW_2
	  break; 
  case RED_2:
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); // YELLOW_2
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3); // RED_2 
	  next_state = GREEN_1;
	  Timer1_disable();	
	  Timer0_init(1); 
	  break;	
  case GREEN_ps_2:
	  Timer1_init(2); 
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); // YELLOW_2
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0); // GREEN_2
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3); // RED_2
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0); // RED_ps_2
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1); // GREEN_ps_2
	  next_state_2 = RED_ps_2; 
	break;
  case RED_ps_2:
	  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); // YELLOW_2
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2); // RED_ps_1
	  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0); // GREEN_ps_1
	  next_state_2 = GREEN_2;
	  Timer1_init(1); 
	  reset_traffic_1();
	break; 
	}
}

// This functions initialize Timer 0 with given time as parameter 
void Timer0_init(int_32 time)
{
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0); 
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
  {
  }
  TimerDisable(TIMER0_BASE, TIMER_BOTH); // DISABLE
  // Configuration
  TimerConfigure(TIMER0_BASE, (TIMER_CFG_PERIODIC | TIMER_CFG_A_ACT_TOINTD)); 
  TimerLoadSet(TIMER0_BASE , TIMER_A, (time * 16000000)-1);
  // Timer interrupt 
  TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0_handler);
  TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
  // NVIC interrupt 
  IntEnable(INT_TIMER0A_TM4C123);
  // CPU interrupt
  IntMasterEnable();
  TimerEnable(TIMER0_BASE, TIMER_BOTH); // ENABLE
  
}

// This functions initialize Timer 1 with given time as parameter 
void Timer1_init(int_32 time)
{
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1); 
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1))
  {
  }
  TimerDisable(TIMER1_BASE, TIMER_BOTH); // DISABLE
  // Configuration
  TimerConfigure(TIMER1_BASE, (TIMER_CFG_PERIODIC | TIMER_CFG_A_ACT_TOINTD)); 
  TimerLoadSet(TIMER1_BASE , TIMER_A, (time * 16000000)-1);
  // Timer interrupt 
  TimerIntRegister(TIMER1_BASE, TIMER_A, Timer1_handler);
  TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
  // NVIC interrupt 
  IntEnable(INT_TIMER1A_TM4C123);
  // CPU interrupt
  IntMasterEnable();
  TimerEnable(TIMER1_BASE, TIMER_BOTH); // ENABLE
}





// Function initializes the corresponding port A

/* function initializes the corresponding port with all functionalities needed*/
void PORTA_init()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){ }
  HWREG(GPIO_PORTA_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTA_BASE + GPIO_O_CR) |= GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
  GPIOPadConfigSet(GPIO_PORTA_BASE,GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
}



// Function initializes the corresponding port B

/* function initializes the corresponding port with all functionalities needed*/
void PORTB_init()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){ }
  HWREG(GPIO_PORTB_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTB_BASE + GPIO_O_CR) |=  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; 
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_4 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3);
  GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_4 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
}



// Function initializes the corresponding port C

/* function initializes the corresponding port with all functionalities needed*/

void PORTC_init()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)){ }
  HWREG(GPIO_PORTC_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
   HWREG(GPIO_PORTC_BASE + GPIO_O_CR) |= GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 
                                      | GPIO_PIN_7;
  GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 
                                      | GPIO_PIN_7);
  GPIOPadConfigSet(GPIO_PORTC_BASE,  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 
                                      | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
}
		


// Function initializes the corresponding port D

/* function initializes the corresponding port with all functionalities needed*/

void PORTD_init()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){ }
  HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
 HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |=  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
 GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_0);
 GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6);
 GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
  // **GPIO interrupt** 
  GPIOIntRegister(GPIO_PORTD_BASE, switch2_handler); 
  GPIOIntEnable(GPIO_PORTD_BASE, GPIO_INT_PIN_0);
  // NVIC interrupt 
  IntEnable(INT_GPIOD_TM4C123);
  // CPU interrupt
  IntMasterEnable();
}
		


// Function initializes the corresponding port E

/* function initializes the corresponding port with all functionalities needed*/

void PORTE_init()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)){ }
  HWREG(GPIO_PORTE_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTE_BASE + GPIO_O_CR) |=  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
 GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
 GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
}



// Function initializes the corresponding port F

/* function initializes the corresponding port with all functionalities needed*/

void PORTF_init()
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)){ }
  HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
 HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |=  GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                                      | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
 GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,
    GPIO_PIN_0 | GPIO_PIN_4);
 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
 GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
  
  // **GPIO interrupt** 
  GPIOIntRegister(GPIO_PORTF_BASE, switch_handler); 
  GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_4);
  // NVIC interrupt 
  IntEnable(INT_GPIOF_TM4C123);
  // CPU interrupt
  IntMasterEnable();
  

}

//This function check which switch has created the interruput

/*This function check which switch has created the interrupt and move to the corresponding handler.*/
void switch_handler()
{
   GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_4);
   Delay(DELAY_DEBOUNCE);
   if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_0)) == 0) {
    switch1_handler();
  }
  else if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == 0) {
    switch2_handler();
  }
  else if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_0)) == 0 && GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == 0)
  {
	 next_state = GREEN_ps_1; 
	 next_state_2 = GREEN_ps_2;
	 switch1_handler();
	 switch2_handler();
	 
  }
}

//function stores the elapsed time from the corresponding timer and calls its corresponding handler.
void switch1_handler()
{
	elapsed_time_1 = TimerValueGet(TIMER0_BASE, TIMER_A);
	next_state = GREEN_ps_1;
	Timer0_handler();
}

//function stores the elapsed time from the corresponding timer and calls its corresponding handler.
void switch2_handler()
{
	elapsed_time_2 = TimerValueGet(TIMER1_BASE, TIMER_A);
	next_state_2 = GREEN_ps_2;
	Timer1_handler();

}


// This function disables timer A 
void Timer0_dsiable()
{
 TimerDisable(TIMER0_BASE, TIMER_BOTH); 
}

// This function disables timer B
void Timer1_disable()
{
  TimerDisable(TIMER1_BASE, TIMER_BOTH);
}


// This function put the system into the start state
void Traffic_light_init()
{
  
  GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2); // RED_ps_2
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5); // RED_ps_1
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3); // RED_2
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, GPIO_PIN_4); // RED_2
  Timer0_init(1);
}

// Convert ticks into time in seconds
int_32 Ticks_to_time(int_32 elapsed_ticks)
{
  return (elapsed_ticks / 16000000);
}


// Delay is used to switch presses check 
void Delay(unsigned long counter)
{
	unsigned long i = 0;
	for(i = 0; i<counter; i++);	
}


// This function reset traffic light 1

void reset_traffic_1()
{
  Timer0_dsiable();
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0); // YELLOW_1
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0); // GREEN_1
  GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, GPIO_PIN_2); // RED_1
}

// This function reset traffic light 2

void reset_traffic_2()
{
  Timer1_disable();
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); // YELLOW_2
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0); // GREEN_2
  GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_PIN_3); // RED_2
}

