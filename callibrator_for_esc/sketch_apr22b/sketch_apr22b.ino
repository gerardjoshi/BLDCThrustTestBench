#include <Servo.h>

Servo esc;

void setup() {
  Serial.begin(115200);
  
  esc.attach(3); // Attach ESC signal wire to pin 9
  esc.writeMicroseconds(2000); // Send max throttle for calibration
  
  Serial.println("Sending MAX throttle (2000 µs)... Plug in ESC power now!");
  delay(5000); // Wait 5 seconds for user to connect ESC power
  
  esc.writeMicroseconds(1000); // Send min throttle to complete calibration
  Serial.println("Now sending MIN throttle (1000 µs). Calibration should be done.");
  delay(2000);
}

void loop() {
  esc.writeMicroseconds(1000); // Keep ESC armed at low throttle
}
