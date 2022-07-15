//Libraries

#include <LiquidCrystal_I2C.h>
#include <DHT.h>


//Constants

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


//Variables

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // LCD screen address
float hum;  // Stores humidity value
float temp; // Stores temperature value
float soil_hum; // Stores soil humidity value


void setup() {
  
  // Initialising peripherals
  lcd.init();
  lcd.backlight();
  dht.begin();
  
}


void loop() {

    // Get sensor readings
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    soil_hum = analogRead(0);
    
    //Display to the LCD
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
    
    //Delay 2 sec
    delay(2000); 
  
}
