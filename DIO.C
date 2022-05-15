#include "DIO.h" // Include DIO.h file 


//**** Definition of DIO.c file ****

//Inizialization function
void DIO_INIT(int_32 port, int_32 pin, int_32 dir){ 

    SET_BIT(SYSCTL_RCGCGPIO_R, port);
    while(GET_BIT(SYSCTL_PRGPIO_R, port) == 0){};
    
    switch (port){
        case PORTA:
        GPIO_PORTA_LOCK_R = 0x4C4F434B;
        GPIO_PORTA_DIR_R |= (1<<pin);
        if(!dir){
        TOGGLE_BIT(GPIO_PORTA_DIR_R,pin);
        SET_BIT(GPIO_PORTA_PUR_R, pin);
        }
        SET_BIT(GPIO_PORTA_DEN_R, pin)
        GPIO_PORTA_CR_R = 0xFF;
            break;

        case PORTB:
        GPIO_PORTB_LOCK_R = 0x4C4F434B;
        GPIO_PORTB_DIR_R |= (1<<pin);
        if(!dir){
        TOGGLE_BIT(GPIO_PORTB_DIR_R,pin);
        SET_BIT(GPIO_PORTB_PUR_R, pin);
        }
        SET_BIT(GPIO_PORTB_DEN_R, pin)
        GPIO_PORTB_CR_R = 0xFF;

            break;

        case PORTC:
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        GPIO_PORTC_DIR_R |= (1<<pin);
        if(!dir){
        TOGGLE_BIT(GPIO_PORTC_DIR_R,pin);
        SET_BIT(GPIO_PORTC_PUR_R, pin);
        }
        SET_BIT(GPIO_PORTC_DEN_R, pin)
        GPIO_PORTC_CR_R = 0xFF;

            break;


        case PORTD:
        GPIO_PORTD_LOCK_R = 0x4C4F434B;
         GPIO_PORTD_DIR_R |= (1<<pin);
        if(!dir){
        TOGGLE_BIT(GPIO_PORTD_DIR_R,pin);
        SET_BIT(GPIO_PORTD_PUR_R, pin);
        }
        SET_BIT(GPIO_PORTD_DEN_R, pin)
        GPIO_PORTD_CR_R = 0xFF;

            break;


        case PORTE:
        GPIO_PORTE_LOCK_R = 0x4C4F434B;
        GPIO_PORTE_DIR_R |= (1<<pin);
        if(!dir){
        TOGGLE_BIT(GPIO_PORTE_DIR_R,pin);
        SET_BIT(GPIO_PORTE_PUR_R, pin);
        }
        SET_BIT(GPIO_PORTE_DEN_R, pin)
        GPIO_PORTE_CR_R = 0xFF;

            break;

        
        case PORTF:
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        GPIO_PORTF_DIR_R |= (1<<pin);
        if(!dir){
        TOGGLE_BIT(GPIO_PORTF_DIR_R,pin);
        SET_BIT(GPIO_PORTF_PUR_R, pin);
        }
        GPIO_PORTF_CR_R = 0xFF;
        SET_BIT(GPIO_PORTF_DEN_R, pin)
            break;
        default:
            break;
        }
}

// Write value to pin
void write_pin(int_8 port, int_8 pin, int_8 value)
{
  switch (port)
  {
  case PORTA: 
    if (GET_BIT(GPIO_PORTA_DEN_R, pin) && GET_BIT(GPIO_PORTA_DIR_R, pin))
    {
      if (value)
      {
        SET_BIT(GPIO_PORTA_DATA_R, pin)
      }
      else
      {
        CLEAR_BIT(GPIO_PORTA_DATA_R, pin)
      }
    }
    
    
  case PORTB: 
   if (GET_BIT(GPIO_PORTB_DEN_R, pin)&& GET_BIT(GPIO_PORTB_DIR_R, pin))
    {
      if (value)
      {
        SET_BIT(GPIO_PORTB_DATA_R, pin)
      }
      else
      {
        CLEAR_BIT(GPIO_PORTB_DATA_R, pin)
      }
    }
    
    
  case PORTC: 
   if (GET_BIT(GPIO_PORTC_DEN_R, pin) && GET_BIT(GPIO_PORTC_DIR_R, pin))
    {
      if (value)
      {
        SET_BIT(GPIO_PORTC_DATA_R, pin)
      }
      else
      {
        CLEAR_BIT(GPIO_PORTC_DATA_R, pin)
      }
    }
    
    
  case PORTD: 
   if (GET_BIT(GPIO_PORTD_DEN_R, pin) && GET_BIT(GPIO_PORTD_DIR_R, pin))
    {
      if (value)
      {
        SET_BIT(GPIO_PORTD_DATA_R, pin)
      }
      else
      {
        CLEAR_BIT(GPIO_PORTD_DATA_R, pin)
      }
    }
    
    
  case PORTE: 
    if (GET_BIT(GPIO_PORTE_DEN_R, pin) && GET_BIT(GPIO_PORTE_DIR_R, pin))
    {
      if (value)
      {
        SET_BIT(GPIO_PORTE_DATA_R, pin)
      }
      else
      {
        CLEAR_BIT(GPIO_PORTE_DATA_R, pin)
      }
    }
    
    
    
  case PORTF: 
    if (GET_BIT(GPIO_PORTF_DEN_R, pin) && GET_BIT(GPIO_PORTF_DIR_R, pin))
    {
      if (value)
      {
        SET_BIT(GPIO_PORTF_DATA_R, pin)
      }
      else
      {
        CLEAR_BIT(GPIO_PORTF_DATA_R, pin)
      }
    }
    
  }
}
 
// Write value to port 
void write_port(int_8 port, int_8 value) 
{  
  for (int i = 0; i < 8; i++)
  {
    write_pin(port, i, GET_BIT(value,i));
  }
}

// Read value from port            
int_8 read_port(int_8 port) 
{  
  int_8 port_reading = 0x00; 
  for (int i = 0; i < 8; i++)
  {
    port_reading |= DIO_ReadPin(port, i) << i;
  }
  return port_reading;
}

// Read value from pin
int_8 DIO_ReadPin(int_8 port, int_8 pin)
{
  switch (port)
  {
  case PORTA: 
     if (GET_BIT(GPIO_PORTA_DEN_R, pin) && (!GET_BIT(GPIO_PORTA_DIR_R, pin)))
     {
        return GET_BIT(GPIO_PORTA_DATA_R, pin);
     }
    
  case PORTB: 
    if (GET_BIT(GPIO_PORTB_DEN_R, pin) && (!GET_BIT(GPIO_PORTB_DIR_R, pin)))
     {
        return GET_BIT(GPIO_PORTB_DATA_R, pin);
     }
    
    
  case PORTC: 
   if (GET_BIT(GPIO_PORTC_DEN_R, pin) && (!GET_BIT(GPIO_PORTC_DIR_R, pin)))
     {
        return GET_BIT(GPIO_PORTC_DATA_R, pin);
     }    
    
    
  case PORTD: 
    if (GET_BIT(GPIO_PORTD_DEN_R, pin) && (!GET_BIT(GPIO_PORTD_DIR_R, pin)))
     {
        return GET_BIT(GPIO_PORTD_DATA_R, pin);
     }
        
  case PORTE: 
    if (GET_BIT(GPIO_PORTE_DEN_R, pin) && (!GET_BIT(GPIO_PORTE_DIR_R, pin)))
     {
        return GET_BIT(GPIO_PORTE_DATA_R, pin);
     }    
    
  case PORTF: 
   if (GET_BIT(GPIO_PORTF_DEN_R, pin) && (!GET_BIT(GPIO_PORTF_DIR_R, pin)))
     {
        return GET_BIT(GPIO_PORTF_DATA_R, pin);
     }
   
  default: return -1;
  }
}