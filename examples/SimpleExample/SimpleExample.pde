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

}
