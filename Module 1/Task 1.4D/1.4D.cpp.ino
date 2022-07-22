// Assign pins
const uint8_t BTN_PIN = 2; // pushbutton pin
const uint8_t PIR_PIN = 3;

const uint8_t LED_PIN1 = PB5; // LED pin
const uint8_t LED_PIN2 = PB4;
const uint8_t LED_PIN3 = PB3;

// Counter and compare values

const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;


// Initialise the board
void setup()
{
  // set the button pin as input with a pullup resistor
  pinMode(BTN_PIN, INPUT_PULLUP);
  
  // set the LED pins as output
  DDRB |= (1 << LED_PIN1);
  DDRB |= (1 << LED_PIN2);
  DDRB |= (1 << LED_PIN3);

  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  
  // Prescaler 256
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);
  
  // Loads the timer with 0
  TCNT1 = t1_load;

  //Set timer compare
  OCR1A = t1_comp;
  
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  
  sei();
  
  // begin the serial monitor
  Serial.begin(9600);
  
  attachInterrupt(0, btn_ISR, CHANGE);
  attachInterrupt(1, pir_ISR, CHANGE);
  
}

void loop()
{
  delay(500);
}

void btn_ISR() {
  PORTB ^= (1 << LED_PIN1);
  Serial.println("Button on.");
}

void pir_ISR() {
  PORTB ^= (1 << LED_PIN2);
  Serial.println("PIR on.");
}

ISR(TIMER1_COMPA_vect) {
  TCNT1 = t1_load;
  PORTB ^= (1 << LED_PIN3);
  Serial.println("Flashing!.");
}