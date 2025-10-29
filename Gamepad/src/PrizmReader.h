#ifndef PRIZM_READER_H
#define PRIZM_READER_H

#include "IGamepadReader.h" // Include the contract it must fulfill

/**
 * @brief A concrete implementation of IGamepadReader for the TETRIX PRIZM controller.
 *
 * This class knows how to communicate specifically with the PRIZM's analog
 * input ports to read PWM signals from an RC receiver.
 */
class PrizmReader : public IGamepadReader {
public:
  PrizmReader();

  // Override and implement the functions promised in the IGamepadReader interface.
  void begin() override;
  int readRawValue(int port) override;
};

#endif // PRIZM_READER_H