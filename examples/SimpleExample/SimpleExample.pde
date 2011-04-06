/**
   JoystickShield - Arduino Library for JoystickShield (http://sudarmuthu.com/arduino/joystickshield)

   Copyright 2011  Sudar Muthu  (email : sudar@sudarmuthu.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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
