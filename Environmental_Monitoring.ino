#include <LiquidCrystal.h>

// LCD connections: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensor pins
const int LDR_PIN = A0;
const int TEMP_PIN = A1;

// Relay control through NPN transistor
const int RELAY_PIN = 7;

// Temperature threshold
const float TEMP_THRESHOLD = 30.0;

void setup() {
  // Initialize relay control
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("System Starting");
  delay(1500);
  lcd.clear();

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("System Ready");
}

void loop() {
  // Read light sensor
  int lightValue = analogRead(LDR_PIN);

  // Read TMP36 temperature sensor
  int tempReading = analogRead(TEMP_PIN);
  float voltage = tempReading * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;

  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  // Display light level
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(lightValue);
  lcd.print("    ");

  // Display sensor readings in Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" C | Light: ");
  Serial.println(lightValue);

  // Control fan based on temperature
  if (temperature >= TEMP_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Fan ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Fan OFF");
  }

  delay(1000);
}
