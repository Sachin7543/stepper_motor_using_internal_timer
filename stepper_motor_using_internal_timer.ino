#define dirPin 51
#define stepPin 49
int state = 0;
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

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 30;       // compare match register 16MHz/256/2Hz
  TCCR1B = TCCR1B | (1 << WGM12);  // CTC mode
  TCCR1B = TCCR1B | ((1 << CS12) | (1 << CS10)); // 256 prescaler
  TIMSK1 = TIMSK1 | (1 << OCIE1A); // enable timer compare interrup
  Serial.begin(9600);
}
void loop()
{
   digitalWrite(dirPin, HIGH);
}

ISR(TIMER0_COMPA_vect)          // timer compare interrupt service routine
{ 
  digitalWrite(stepPin, HIGH);
}
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
   digitalWrite(stepPin, LOW);
}
