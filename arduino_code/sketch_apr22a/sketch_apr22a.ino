#include <Servo.h>
#include "HX711.h"
#include "max6675.h"

// ESC setup
Servo esc;
const int escPin = 3;

// Load Cell HX711
#define HX711_DOUT 6
#define HX711_SCK 7
HX711 scale;

// Thermocouple MAX6675
#define MAX6675_SO 11
#define MAX6675_CS 12
#define MAX6675_SCK 13
MAX6675 thermocouple(MAX6675_SCK, MAX6675_CS, MAX6675_SO);

// Current Sensor (ACS712)
const int currentSensorPin = A0;
const float VCC = 5.0;
const float sensitivity = 0.066; // For 30A sensor
float zeroCurrentVoltage = 2.5;

void setup() {
  delay(6000);
  Serial.begin(115200);
  esc.attach(escPin);
  esc.writeMicroseconds(1000);
  delay(3000); // Arm ESC

  // Load Cell
  scale.begin(HX711_DOUT, HX711_SCK);
  scale.set_scale(280); 
  scale.tare();

  // Calibrate ACS712 zero-current offset
  zeroCurrentVoltage = analogRead(currentSensorPin) * (VCC / 1023.0);

  // Print CSV header
  Serial.println("PWM,Current (A),Load (g),Temp (C)");
}

void loop() {
  for (int pwm = 1000; pwm <= 2000; pwm += 100) {
    esc.writeMicroseconds(pwm);
    delay(4000); // Hold each torque level for 4 seconds

    float sensorVoltage = analogRead(currentSensorPin) * (VCC / 1023.0);
    float current = -((sensorVoltage - zeroCurrentVoltage) / sensitivity);
    float load = scale.get_units(5); // Take average of 5 readings
    float temp = thermocouple.readCelsius();

    // CSV-style output
    Serial.print(pwm); Serial.print(",");
    Serial.print(current, 2); Serial.print(",");
    Serial.print(load, 2); Serial.print(",");
    Serial.println(temp, 2);
  }

  esc.writeMicroseconds(1000); // Stop motor
  Serial.println("Test complete.");
  while (true); // Halt
}
