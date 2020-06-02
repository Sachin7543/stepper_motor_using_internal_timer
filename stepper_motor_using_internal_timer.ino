#define dirPin 51
#define stepPin 49
int state = 10000;
int i = 0;
void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  // initialize timer1 
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;
  OCR0A = 249;            // compare match register 16MHz/256/2Hz
  TCCR0B = TCCR0B |(1 << WGM01);   // CTC mode
  TCCR0B |= (1 << CS01);   // 64 prescaler
  TCCR0B |= (1 << CS00); 
  TIMSK0 = TIMSK0 |(1 << OCIE0A);  // enable timer compare interrupt
  sei();             // enable all interrupts
  Serial.begin(9600);

}
void loop()
{
   digitalWrite(dirPin, HIGH);
   if ( i  < state)
   {
      digitalWrite(stepPin, LOW); 
   }
   else
   {
    i = 0;
   }
}

ISR(TIMER0_COMPA_vect)          // timer compare interrupt service routine
{
  i++;          
}
