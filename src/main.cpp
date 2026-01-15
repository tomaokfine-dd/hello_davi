#include <Arduino.h>

const float ADC_MAX = 4095.0;
const float VREF = 3.3;
const int NUM_SAMPLES = 20;

// Use A0/A1 instead of hardcoding GPIO 34/35
const int ADC_PIN_A = D0;   // When VOUT1 or VOUT2 is connected to D0, it usually maps to A0
const int ADC_PIN_B = D1;   // When the other channel is connected to D1, it usually maps to A1

float readAveragedADC(int pin) {
  long sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += analogRead(pin);
    delay(2);
  }
  return sum / (float)NUM_SAMPLES;
}

void setup() {
  Serial.begin(115200);
  delay(200);

  analogReadResolution(12);

  // Note: On some boards, only A0/A1 are mapped to ADC-capable pins.
  // Explicitly setting attenuation improves stability.
  analogSetPinAttenuation(ADC_PIN_A, ADC_11db);
  analogSetPinAttenuation(ADC_PIN_B, ADC_11db);

  Serial.println("ADC_A, V_A(V), ADC_B, V_B(V)");
}

void loop() {
  float rawA = readAveragedADC(ADC_PIN_A);
  float rawB = readAveragedADC(ADC_PIN_B);

  float vA = (rawA / ADC_MAX) * VREF;
  float vB = (rawB / ADC_MAX) * VREF;

  Serial.print((int)rawA);
  Serial.print(", ");
  Serial.print(vA, 3);
  Serial.print(", ");
  Serial.print((int)rawB);
  Serial.print(", ");
  Serial.println(vB, 3);

  delay(300);
}
