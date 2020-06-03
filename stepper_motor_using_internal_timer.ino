#define dirPin 51
#define stepPin 49
int state = 0;
int Direction_control = 1;
float value1 = 0;
int flag = 0;
int flag1 = 0;
int flag2 = -1;
int value;
float value2 = 14;
int steps = 200;
int i = 1;
void setup()
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  //OCR1A  = 14;       // compare match register 16MHz/256/2Hz
  TCCR1B = TCCR1B | (1 << WGM12);  // CTC mode
  TCCR1B = TCCR1B | ((1 << CS12) | (1 << CS10)); // 256 prescaler
  TIMSK1 = TIMSK1 | (1 << OCIE1A); // enable timer compare interrup
  sei();
  Serial.begin(9600);
  Serial.println("SR.NO          Description               *  Keys ");
  Serial.println("*************************************************");
  Serial.println("  1)  For changing the direction PRESS   *   1");
  Serial.println("  2)  For changing the Speed TYPE        * SPEED");
  Serial.println("  3)  For Start the Motor TYPE           * START");
  Serial.println("  4)  For Stop the Motor TYPE            * STOP");
  Serial.println("  5)  For increase Stpe of Motor TYPE    * STEP");
  Serial.println("*************************************************");
}
void loop()
{
  if (Serial.available() > 0)
  {
    String read_input = Serial.readString();
    Serial.println(read_input);
    read_input.trim();
    read_input.toUpperCase();
    if(read_input == "START")
    {
       OCR1A  = 14;
       flag2 = 0; 
       i=0;   
       Serial.println("MOTOR ON");
   
    }
    value = read_input.toInt();
    if (value == 1)
      Direction_control = !Direction_control;
    if (read_input == "SPEED")
    {
      flag = 1;
      Serial.println("Please pass motor speed in rpm Example:- 60,100");
    }
    if (flag == 1 && (value > 0 && value != 1))
    {
      value1 = read_timer_up(value);
      if ( value1 > 0 && value1 < 65536)
      {
        value2=value1;
        Serial.println("Speed is Set "+(String)value +"rpm");
      }
      if (((int)value1 <= 0 || (int)value1 > 65536))
      {
        digitalWrite(dirPin, LOW);
        digitalWrite(stepPin, LOW);
        flag2 = 1;
        
      }
      flag = 0;
    }
    if ( read_input == "STEP")
    {
      flag1 = 1;
    
    }
    if (read_input == "STOP")
    {
        digitalWrite(dirPin, LOW);
        digitalWrite(stepPin, LOW);
        flag2 = 1;
        Serial.println("MOTOR OFF");
    }
    if (flag1 == 1 && value > 0) {
      Step(value);
      flag1=0;
      i = 0;
      Serial.println("New step value is set"+(String)value);
    }
  }
}
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{

  if(flag2 != 1 && flag2 == 0){
  OCR1A  = (int)value2;
  if(i < steps){
  Serial.println(i);
  digitalWrite(dirPin, Direction_control);
  state = !state;
  digitalWrite(stepPin, state);
  i++;
  }
  }
}
void Step(int number_of_steps)
{
  steps = number_of_steps;
}

float read_timer_up(int val)
{
  // calu the Revolution per minute //
  return 60L * 1000L / steps / val;
}
