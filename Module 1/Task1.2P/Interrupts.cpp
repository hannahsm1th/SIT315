//Libraries

#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <LowPower.h>


//Constants

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
const byte interrupt_pin = 3;
volatile byte state = LOW;


//Variables

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // LCD screen address
float hum;  // Stores humidity value
float temp; // Stores temperature value
float soil_hum; // Stores soil humidity value


void setup() {
  pinMode(3, INPUT);
  // Initialising peripherals
  lcd.init();
  lcd.clear();
  dht.begin();
  
}


void loop() {
  
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),interrupt_routine,RISING);
  LowPower.powerDown(SLEEP_FOREVER,ADC_OFF,BOD_OFF); // sleep until interrupt
  detachInterrupt(digitalPinToInterrupt(interrupt_pin)); // remove interrupt
  
  if (state==HIGH){
    displayReadings();
    delay(5000);
  }
  if (state==HIGH) {
    state = LOW;
    lcd.noBacklight();
  }
  
}

void interrupt_routine(){
  state = HIGH;
}

void displayReadings() {
  // Get sensor readings
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    soil_hum = analogRead(0);
    
    //Display to the LCD
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("");
    lcd.print(temp);
    lcd.print("C  ");
    lcd.print(hum);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("");
    lcd.print(soil_hum);
    if (soil_hum < 300 ){lcd.print(" DRY");}
    else if (soil_hum > 299 && soil_hum < 700 ){lcd.print(" HUMID");}
    else if (soil_hum > 699 ){lcd.print(" WET");}
    else {lcd.print(" ERROR");}
}
