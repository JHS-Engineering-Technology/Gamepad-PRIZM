#ifndef IGAMEPAD_READER_H
#define IGAMEPAD_READER_H

/**
 * @brief The interface (contract) for all hardware-specific gamepad readers.
 *
 * This abstract class defines the essential functions that any concrete reader
 * implementation must provide. It ensures that the main Gamepad library can
 * communicate with any supported hardware in a standardized way.
 */
class IGamepadReader {
public:
  // Virtual destructor is crucial for classes intended for inheritance.
  virtual ~IGamepadReader() {}

  /**
   * @brief Initializes the hardware-specific components (e.g., setting pin modes).
   */
  virtual void begin() = 0;

  /**
   * @brief Reads a raw, unprocessed integer value from a specific hardware port.
   * @param port The logical port number (e.g., 1, 2, 3) to read from.
   * @return The raw signal value from the hardware (e.g., a PWM pulse width).
   */
  virtual int readRawValue(int port) = 0;
};

#endif // IGAMEPAD_READER_H