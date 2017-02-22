
#define LED PORTB5  //Button 4
#define LED_REFRESH 500  //Button 4


volatile int16_t LEDTick=LED_REFRESH, ADCTick=0, GeneralTick=0, EncoderTick=0; //Interrupt timer variables

void setup() {

  DDRB |= (1<<LED); // LED13 Output

  timer0_init();
  
}
void timer0_init() // Timer 0 Setup to give 1ms counts
{
  // set up timer with CTC mode
  TCCR0A |= (1 << WGM01);
  
  // initialize counter
  TCNT0 = 0;
  
  // initialize compare value 125
  OCR0A = 0x7d;
  
  // enable compare interrupt
  TIMSK0 |= (1 << OCIE0A);
  
  //Start the timer with prescaler = 64
  TCCR0B |= (1 << CS01) | (1 << CS00);
  
  // enable global interrupts
  sei();
}

// Basic Tick Interrupt 
ISR (TIMER0_COMPA_vect)
{
  LEDTick --;  //16 bit 0 - 65536 but reset every LCDTick
 //ADCTick --;  //16 bit 0 - 65536 but reset every ADCTick
 //EncoderTick --;  //16 bit 0 - 65536 but reset every EncoderTick
 //GeneralTick ++;  //16 bit 0 - 65536
}

void ToggleLED()
{
PORTB ^= (1<<LED);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if (LEDTick <= 0)
  {
    ToggleLED();
    LEDTick = LED_REFRESH;
  }
  }
