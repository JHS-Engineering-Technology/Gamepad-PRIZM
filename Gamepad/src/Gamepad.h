/**
 * @file Gamepad.h
 * @brief Header file for the Gamepad C++ library.
 * @author Shanti Vince Mansel (JHS Engineering)
 * @date 2025-10-17
 * @license This code is released under the MIT License.
 */

#ifndef GAMEPAD_H
#define GAMEPAD_H

class IGamepadReader; // Forward-declaration to avoid circular includes

// --- Public API Constants ---
// The Gamepad library provides processed values within this universal range.
#define JOY_HIGH 100
#define JOY_LOW -100

/**
 * @brief Defines the logical axes of a standard gamepad.
 *
 * This enum provides human-readable names for the joystick axes that the user
 * will interact with in their code.
 */
enum GamepadAxis {
  GAMEPAD_AXIS_RIGHT_X, // Standard mapping to RCVR Channel 1
  GAMEPAD_AXIS_LEFT_Y,  // Standard mapping to RCVR Channel 2
  GAMEPAD_AXIS_RIGHT_Y, // Standard mapping to RCVR Channel 3
  GAMEPAD_AXIS_LEFT_X   // Standard mapping to RCVR Channel 4
};

/**
 * @brief The main Gamepad library class.
 *
 * This class provides a high-level, hardware-agnostic interface for reading
 * joystick values. It handles all the signal processing logic.
 */
class Gamepad {
public:
  Gamepad(IGamepadReader* reader);
  void begin();
  void update();
  int readAxis(GamepadAxis axis);

  // Allows the user to create a custom mapping between a logical axis and a physical hardware port.
  void mapAxisToPort(GamepadAxis axis, int port);

private:
  IGamepadReader* _reader; // Pointer to the injected hardware reader
  int _axisMapping[4];     // Stores the user-defined mappings
  int _processedValues[4]; // Stores the latest processed joystick values

  // Private helper function to convert raw PWM signals into clean joystick values.
  int mapToJoyValue(long pulseWidth);
};

#endif // GAMEPAD_H