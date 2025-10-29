# Gamepad-PRIZM
An Arduino IDE Ready .zip file RELEASE for student assignments. Includes the Tank Drive example

# TETRIX PRIZM Gamepad Library

A simple, hardware-abstracted Arduino library for reading a TETRIX RC receiver with a PRIZM controller. It handles all the signal processing (trim, deadband) and provides clean joystick values from **-100 to 100**.

This library provides a default mapping for a common "tank drive" or "arcade drive" setup:
* **Left Stick X-Axis:** Port 1
* **Left Stick Y-Axis:** Port 2
* **Right Stick Y-Axis:** Port 3

---

## ⚠️ Prerequisite: Install "PRIZM" Library

Before you can use this library, you **must** install the official "PRIZM" library by TETRIX Robotics.

1.  In the Arduino IDE, go to **Tools > Manage Libraries...**
2.  Search for `PRIZM` and install the library.



---

## Installation (Choose One)

You only need to install the `Gamepad` library using **one** of the methods below.

### Method 1 (Recommended): Download from GitHub

This is the easiest way to get the latest stable version.

1.  Go to the library's GitHub page: [**github.com/JHS-Engineering-Technology/Gamepad-PRIZM/releases**](https://github.com/JHS-Engineering-Technology/Gamepad-PRIZM/releases)
2.  Under the latest release, click `Gamepad.zip` to download the library.
3.  In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
4.  Select the `Gamepad.zip` file you just downloaded.

### Method 2: Install from Google Drive

1.  Download the `Gamepad.zip` file from the Google Drive link provided by your instructor.
2.  In the Arduino IDE, go to **Sketch > Include Library > Add .ZIP Library...**
3.  Select the `Gamepad.zip` file you downloaded.

---

---

## How to Use

Once installed, you can find a complete, working example:

1.  Go to **File > Examples > Gamepad > TankDrive**.
2.  This sketch will show you how to initialize the library and read the joystick values to control a simple tank-drive robot.

## Library Structure

This repository contains the files for the Arduino library.
```
Gamepad/
├── library.properties
│
├── src/
│   ├── Gamepad.h
│   ├── Gamepad.cpp
│   ├── IGamepadReader.h
│   ├── PrizmReader.h
│   └── PrizmReader.cpp
│
└── examples/
    └── TankDrive/
        └── TankDrive.ino
```
