#define dirPin 51
#define stepPin 49
int state = 0;
void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A  = 77;       // compare match register 16MHz/256/2Hz
  TCCR1B = TCCR1B | (1 << WGM12);  // CTC mode
  TCCR1B = TCCR1B | ((1 << CS12) | (1 << CS10)); // 256 prescaler
  TIMSK1 = TIMSK1 | (1 << OCIE1A); // enable timer compare interrup
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(dirPin, HIGH);
}
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
   state = !state;
   Serial.println(state);
   digitalWrite(stepPin, state);
}
