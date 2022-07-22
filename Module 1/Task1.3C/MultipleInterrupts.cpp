// Assign pins
const uint8_t BTN_PIN = 2; // pushbutton pin
const uint8_t PIR_PIN = 3; // PIR pin
const uint8_t LED_PIN1 = 13; // red LED pin
const uint8_t LED_PIN2 = 12; // blue LED pin

// Initial states for our device pin variables
uint8_t buttonState = LOW;
uint8_t pirState = LOW;


// Initialise the board
void setup()
{
  // set the button pin as input with a pullup resistor
  pinMode(BTN_PIN, INPUT_PULLUP);
  // set the LED pins as output
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  // begin the serial monitor
  Serial.begin(9600);
  // attach interrupts
  attachInterrupt(0, btn_ISR, CHANGE);
  attachInterrupt(1, pir_ISR, CHANGE);
}

void loop()
{
}

void btn_ISR() {
  buttonState = digitalRead(BTN_PIN);
  digitalWrite(LED_PIN1, buttonState);
  Serial.println("Button on.");
}

void pir_ISR() {
  pirState = digitalRead(PIR_PIN);
  digitalWrite(LED_PIN2, pirState);
  Serial.println("PIR on.");
}
