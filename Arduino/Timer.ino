/*
  Código base do Timer desenvolvido para a plataforma Tinkercad
  São configurados os registradores devido à falta da biblioteca TimerOne.h
*/

unsigned long previousMillis = 0;

const long interval = 1000;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(12, OUTPUT);

  // Configuração Timer1
  TCCR1A = 0;
  ICR1H =  0x7A;
  ICR1L =  0x12;
  TCCR1B = _BV(WGM13) | _BV(CS12);
  
  // Inicialização Timer1
  TCNT1 = 0;
  TIFR1 = 0;
  TIMSK1 = _BV(TOIE1);
}

void loop() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(1000);
}

ISR(TIMER1_OVF_vect)
{
  digitalWrite(12, !digitalRead(12));
}
