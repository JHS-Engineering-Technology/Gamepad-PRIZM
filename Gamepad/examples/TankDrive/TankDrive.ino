/*
 * TankDrive Example
 * * This sketch shows how to use the Gamepad library for a simple
 * tank drive robot.
 * - The Left Y-Axis controls the Left Motor.
 * - The Right Y-Axis controls the Right Motor.
 * * REQUIRED LIBRARIES:
 * 1. This Gamepad library
 * 2. The "PRIZM" library by TETRIX (must be installed separately)
 */

#include <PRIZM.h>      // Must be installed separately!
#include <Gamepad.h>
#include <PrizmReader.h>

// --- 1. Create Objects ---
PRIZM prizm;
PrizmReader myPrizmReader;
Gamepad gamepad(&myPrizmReader);

void setup() {
  // 1. Initialize PRIZM and Serial Monitor
  prizm.PrizmBegin();
  Serial.begin(9600);
  Serial.println("Tank Drive Example Started...");

  // 2. Initialize the Gamepad
  // This loads the default mapping:
  // LX = Port 1
  // LY = Port 2
  // RY = Port 3
  gamepad.begin();

  // 3. (Optional) Invert one motor so they spin the same way
  prizm.setMotorInvert(1, 1); // Invert Motor 1
}

void loop() {
  // 1. Poll the gamepad ONCE at the top of the loop
  gamepad.update();

  // 2. Read the axis values for tank drive
  int leftPower  = gamepad.readAxis(GAMEPAD_AXIS_LEFT_Y);
  int rightPower = gamepad.readAxis(GAMEPAD_AXIS_RIGHT_Y);

  // 3. Send power to the motors
  prizm.setMotorPowers(leftPower, rightPower);

  // 4. (Optional) Print values to the Serial Monitor for debugging
  Serial.print("Left Y: ");
  Serial.print(leftPower);
  Serial.print("\t Right Y: ");
  Serial.println(rightPower);

  // 5. Add a small delay
  delay(20);
}