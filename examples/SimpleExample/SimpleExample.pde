/**
   JoystickShield - Arduino Library for JoystickShield (http://hardwarefun.com/projects/joystick-shield)

   Copyright 2011  Sudar Muthu  (email : sudar@sudarmuthu.com)

 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <sudar@sudarmuthu.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer or coffee in return - Sudar
 * ----------------------------------------------------------------------------
 * 2014 edit by Markus Mücke, muecke.ma(a)gmail.com
 * Changes for JoysikShield V1.2
 * added a function to read the amplitude of the joystick
 * added a auto calibrate function for 3.3V and 5V mode
 *
 * Added functions:
 *  Functions for F and E Button
 *  Calibrate Joystick
 *  xAmplitude
 *  yAmplitude
 */

/**
 * Before running this example, stack the JoystickShield on top of Arduino board
 *
 */

#include <JoystickShield.h> // include JoystickShield Library

JoystickShield joystickShield; // create an instance of JoystickShield object

void setup() {
    Serial.begin(9600);
  
    delay(100);
    // new calibration function
    joystickShield.calibrateJoystick();
    
	// predefined Joystick to Pins 0 and 1.
	// Change it if you are using a different shield
	// setJoystickPins(0, 1);
  
	// predefined buttons to the following pins.
	// change it if you are using a different shield.
	// setButtonPins(pinJoystickButton, pinUp, pinRight, pinDown, pinLeft, pinF, pinE);
	// to deactivate a button use a pin outside of the range of the arduino e.g. 255, but not above
	// setButtonPins(8, 2, 3, 4, 5, 7, 6);
}

void loop() {
  joystickShield.processEvents(); // process events

  if (joystickShield.isUp()) {
     Serial.println("Up") ;
  }

  if (joystickShield.isRightUp()) {
     Serial.println("RightUp") ;
  }

  if (joystickShield.isRight()) {
     Serial.println("Right") ;
  }

  if (joystickShield.isRightDown()) {
     Serial.println("RightDown") ;
  }

  if (joystickShield.isDown()) {
     Serial.println("Down") ;
  }

  if (joystickShield.isLeftDown()) {
     Serial.println("LeftDown") ;
  }

  if (joystickShield.isLeft()) {
     Serial.println("Left") ;
  }

  if (joystickShield.isLeftUp()) {
     Serial.println("LeftUp") ;
  }

  if (joystickShield.isJoystickButton()) {
     Serial.println("Joystick Clicked") ;
  }

  if (joystickShield.isUpButton()) {
     Serial.println("Up Button Clicked") ;
  }

  if (joystickShield.isRightButton()) {
     Serial.println("Right Button Clicked") ;
  }

  if (joystickShield.isDownButton()) {
     Serial.println("Down Button Clicked") ;
  }

  if (joystickShield.isLeftButton()) {
     Serial.println("Left Button Clicked") ;
  }

  // new eventfunctions
  if (joystickShield.isEButton()) {
     Serial.println("E Button Clicked") ;
  }

  if (joystickShield.isFButton()) {
     Serial.println("F Button Clicked") ;
  }  
  
  if (joystickShield.isNotCenter()){
     Serial.println("NotCenter") ;
  }
  
  // new position functions
  Serial.print("x ");	Serial.print(joystickShield.xAmplitude());Serial.print(" y ");Serial.println(joystickShield.yAmplitude());

  delay(500);
}
