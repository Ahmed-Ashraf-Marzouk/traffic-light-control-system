#include "Traffic_light.h"

// global variables 

int_32 next_state = GREEN_1; // Traffic light 1 state 
int_32 next_state_2 = RED_2; // Traffic light 2 state 
int_32 next_state_ps = GREEN_ps_1; // Pedstrain 1 state
int_32 elapsed_time_1 = 0; // Elapsed time Green in traffic light 1
int_32 elapsed_time_2 = 0; // Elapsed time Green in traffic light 2
int main()
{
  // Port inizialization 
  PORTA_init();
  PORTC_init();
  PORTE_init();
  PORTF_init();
  PORTD_init();
  // Timer inizialization 
  Timer0_init(1);
  // START
  Traffic_light_init();
  while(1)
  {
	SysCtlSleep(); //Sleep
  }
}
