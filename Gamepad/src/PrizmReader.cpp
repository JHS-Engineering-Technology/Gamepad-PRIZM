#include "PrizmReader.h"
#include <Arduino.h> // Required for Arduino-specific functions like pinMode() and pulseIn()

// --- Internal Hardware Definitions ---
// These physical pin definitions are private to this implementation and are
// not exposed in the header file, improving encapsulation.
#define PRIZM_PIN_FOR_PORT_1 A1
#define PRIZM_PIN_FOR_PORT_2 A2
#define PRIZM_PIN_FOR_PORT_3 A3

PrizmReader::PrizmReader() {
  // Constructor is empty as setup is handled in begin().
}

void PrizmReader::begin() {
  // Configure the physical hardware pins on the PRIZM as inputs.
  pinMode(PRIZM_PIN_FOR_PORT_1, INPUT);
  pinMode(PRIZM_PIN_FOR_PORT_2, INPUT);
  pinMode(PRIZM_PIN_FOR_PORT_3, INPUT);
}

int PrizmReader::readRawValue(int port) {
  int physicalPin;
  const int NEUTRAL_PULSE = 1500; // Safe center value on timeout or error

  // This is the internal mapping from a logical port number to a physical pin.
  switch (port) {
    case 1: physicalPin = PRIZM_PIN_FOR_PORT_1; break;
    case 2: physicalPin = PRIZM_PIN_FOR_PORT_2; break;
    case 3: physicalPin = PRIZM_PIN_FOR_PORT_3; break;
    // Any request for a port not supported by this hardware will fall through.
    default:
      return NEUTRAL_PULSE; // Return neutral if the port is invalid.
  }

  // Read the PWM signal duration
  long rawPulse = pulseIn(physicalPin, HIGH, 50000);

  // If pulseIn() times out, it returns 0. Return a safe neutral value.
  if (rawPulse == 0) {
    return NEUTRAL_PULSE;
  }

  return (int)rawPulse;
}