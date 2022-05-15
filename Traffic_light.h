#include "types.h" // defined types from labs 

// State definitions for each traffic light and pedstrains 

// Traffic_light_1
#define GREEN_1 0
#define YELLOW_1 1
#define RED_1 2 
// Traffic_light_2/
#define GREEN_2 3
#define YELLOW_2 4
#define RED_2 5 
// WAIT states
#define WAIT_1 6
#define WAIT_2 7
// Pedstrain 1
#define GREEN_ps_1 8
#define RED_ps_1 9
#define IDLE 10
// Pedstrain 2
#define GREEN_ps_2 11
#define RED_ps_2 12

// 
//#define PRESSED 20 
//#define NOTPRESSED 21

// delay for swithc press
# define SYSTEM_CLOC_FREQUENCY  80000000
#define DELAY_DEBOUNCE SYSTEM_CLOC_FREQUENCY/100

// Port inizialization 
void PORTA_init();
void PORTB_init();
void PORTC_init(); 
void PORTD_init(); 
void PORTE_init();
void PORTF_init(); 

// inizilize traffic light 
void Traffic_light_init(); 

// switch presses handlers 
void switch1_handler();
void switch2_handler();
void switch_handler();

// Timer inizializatio 
void Timer0_init(int_32 time);
void Timer1_init(int_32 time);

// Timer handlers
void Timer0_handler(); 
void Timer1_handler(); 
void Timer0_dsiable();
void Timer1_disable(); 

// Delay for switch presses check 
void Delay();

// Traffic lights reset 
void reset_traffic_1();
void reset_traffic_2();

// Convert ticks into time in seconds 
int_32 Ticks_to_time(int_32 time);


