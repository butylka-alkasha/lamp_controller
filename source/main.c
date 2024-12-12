#include <avr/io.h>
#define F_CPU 1000000UL // частота резонатора 1МГц
#include <util/delay.h>
#include <avr/interrupt.h>
ISR(INT0_vect)
{
    TCCR0B |=  (1<<CS12) | (1<<CS10);
}
ISR(INT1_vect)
{
    TCCR0B |=  (1<<CS12) | (1<<CS10);
}
ISR(TIMER0_OVF_vect)
{
    if (0 != (PIND & (1<<PD2)))
    {
    if (OCR1A < 318)
    OCR1A ++;
    }
else 
    if (0 != (PIND & (1<<PD3)))
     {
     if (OCR1A > 2)
      OCR1A --;
    }
else

    {
    TCCR0B &= ~(1<<CS12) & ~(1<<CS10);
    TCNT0  = 0;
    }
}
int main (void)
{
  DDRB |= 1 << PB1;
  EICRA |= (1<<ISC01) | (1<<ISC00) | (1<<ISC10) | (1<<ISC11);
  TIMSK0 |= (1<<TOIE0);
  EIMSK |=(1<<INT0) | (1<<INT1);
  DDRB |= (1 << PB1); 
  TCCR1A = 0; 
  TCCR1B = 0; 
  TCNT1  = 0; 
  TCCR1B |= (1 << CS10); 
  TCCR1A |= (1 << COM1A1) | (1 << COM1B0);  
  ICR1    = 320;                            
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1<<CS11) | (1<<CS10);
  OCR1A = 25;
  sei();
  while (1)
  {}
}