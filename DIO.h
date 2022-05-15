//**** Include files ****
#include "types.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"

//**** Define macros ****
#define SET_BIT(REG,PIN) {REG|=(1<<PIN);}
#define CLEAR_BIT(REG,PIN) {REG&= ~(1<<PIN);}
#define TOGGLE_BIT(REG,PIN) {REG^= (1<<PIN);}
#define GET_BIT(REG,PIN) (((1<<PIN)&REG)>>PIN)
#define IN 0
#define OUT 1
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

//**** Light code definition ****
#define GREEN  0
#define YELLOW 1
#define RED    2


//**** DIO functions definitions ****
void DIO_INIT(int_32 port, int_32 pin, int_32 dir);
void write_pin(int_8 port, int_8 pin, int_8 value); 
void write_port(int_8 port, int_8 value);
int_8 DIO_ReadPin(int_8 port, int_8 pin);
int_8 DIO_ReadPort(int_8 port);
int_8 test_DIO_ReadPin(int_8 port, int_8 pin);
