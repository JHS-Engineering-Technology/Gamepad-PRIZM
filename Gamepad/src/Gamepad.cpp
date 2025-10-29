#include "Gamepad.h"
#include "IGamepadReader.h" // Required to call the reader's functions
#include <Arduino.h>                        // Required for map() and abs()

/* --- Hardware Calibration Notes ---
 *
 * The constants below were calibrated using the following empirical PWM measurements
 * from a standard TETRIX RC receiver connected to a PRIZM.
 *
 * // Neutral Position
 * 13:44:48.551 -> Pulse Length LR: 1514 :: UD: 1521
 *
 * // Right Joystick - RCVR Channel 1
 * 13:44:32.934 -> Pulse Length LR: 2030 :: UD: 1515
 * 13:44:37.125 -> Pulse Length LR: 1015 :: UD: 1514
 *
 * // Left Joystick - RCVR Channel 2
 * 13:44:41.251 -> Pulse Length LR: 1521 :: UD: 2030
 * 13:44:45.436 -> Pulse Length LR: 1520 :: UD: 1096
 */

// --- Internal Constants for Signal Processing ---
const int PULSE_WIDTH_HIGH = 2100;
const int PULSE_WIDTH_LOW = 1000;
const int JOYSTICK_CENTER_TRIM = -7;  // An offset to correct for a non-centered joystick.
const int JOYSTICK_DEADBAND    = 5;   // A threshold to ignore minor signal noise near the center.

Gamepad::Gamepad(IGamepadReader* reader) : _reader(reader) {
  // Initialize internal arrays to a known, safe state.
  for (int i = 0; i < 4; i++) {
    _axisMapping[i] = 0;
    _processedValues[i] = 0;
  }
}

void Gamepad::begin() {
  if (_reader) {
    _reader->begin();
  }
  // Provides a sensible, out-of-the-box configuration that matches the
  // standard TETRIX receiver wiring. The user can override this.
// mapAxisToPort(GamepadAxis axis, int port)
  mapAxisToPort(GAMEPAD_AXIS_RIGHT_X, 0); // Unmapped by default (port 0 will read 0)
  mapAxisToPort(GAMEPAD_AXIS_LEFT_Y,  2); // Mapped to Port 2 (e.g., A2)
  mapAxisToPort(GAMEPAD_AXIS_RIGHT_Y, 3); // Mapped to Port 3 (e.g., A3)
  mapAxisToPort(GAMEPAD_AXIS_LEFT_X,  1); // Mapped to Port 1 (e.g., A1)
}

// Converts raw PWM pulses to clean joystick values.
int Gamepad::mapToJoyValue(long pulseWidth) {
  int joyValue = map(pulseWidth, PULSE_WIDTH_LOW, PULSE_WIDTH_HIGH, JOY_LOW, JOY_HIGH) - JOYSTICK_CENTER_TRIM;
  // Apply deadband: if the value is very close to zero, just return zero.
  return abs(joyValue) > JOYSTICK_DEADBAND ? joyValue : 0;
}

// Polls the hardware and processes all channels. Call this once per loop.
void Gamepad::update() {
  if (!_reader) return;

  // Process all four standard axes using the same conversion logic.
  for (int i = 0; i < 4; i++) {
    int portToRead = _axisMapping[i];
    long rawValue = _reader->readRawValue(portToRead);
    _processedValues[i] = mapToJoyValue(rawValue);
  }
}

// Fast accessor function for the user to get the latest processed value.
int Gamepad::readAxis(GamepadAxis axis) {
  if (axis >= GAMEPAD_AXIS_RIGHT_X && axis <= GAMEPAD_AXIS_LEFT_X) {
    return _processedValues[axis];
  }
  return 0; // Return 0 for any invalid axis request.
}

// Allows the user to override the default mapping configuration.
void Gamepad::mapAxisToPort(GamepadAxis axis, int port) {
    if (axis >= GAMEPAD_AXIS_RIGHT_X && axis <= GAMEPAD_AXIS_LEFT_X) {
        _axisMapping[axis] = port;
    }
}