/**
   JoystickShield - Arduino Library for JoystickShield (http://sudarmuthu.com/arduino/joystickshield)

   Copyright 2011  Sudar Muthu  (email : sudar@sudarmuthu.com)

 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <sudar@sudarmuthu.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer or coffee in return - Sudar
 * ----------------------------------------------------------------------------
 */

/**
 * Before running this example, stack the JoystickShield on top of Arduino board
 *
 */

#include <JoystickShield.h> // include JoystickShield Library

JoystickShield joystickShield; // create an instance of JoystickShield object

void setup() {
  Serial.begin(9600);
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
}
