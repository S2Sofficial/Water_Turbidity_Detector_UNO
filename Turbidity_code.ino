#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define sensor_pin A0
int read_ADC;
int ntu;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  pinMode(sensor_pin, INPUT);
  lcd.begin(16, 4); // Initialize the LCD with 16 columns and 4 rows
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Welcome To ");
  lcd.setCursor(0, 1);
  lcd.print("Turbidity Sensor");
  delay(2000);
  lcd.clear();
}

void loop() {
  read_ADC = analogRead(sensor_pin);
  Serial.print("Raw ADC Value: ");
  Serial.println(read_ADC); // Print the raw ADC value to the Serial Monitor

  if (read_ADC > 208) read_ADC = 208; // Cap the ADC value at 208 if it goes above
  ntu = map(read_ADC, 0, 208, 300, 0); // Map the ADC value to NTU value

  Serial.print("NTU Value: ");
  Serial.println(ntu); // Print the NTU value to the Serial Monitor

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Turbidity: ");
  lcd.print(ntu);
  lcd.print(" NTU");

  lcd.setCursor(0, 1); // Set cursor (column, row) indexing from 0
  if (ntu < 10) {
    lcd.print("Water Very Clean");
  } else if (ntu >= 10 && ntu < 30) {
    lcd.print("Water Clean");
  } else if (ntu >= 30) {
    lcd.print("Water Dirty");
  }

  delay(200);
}
