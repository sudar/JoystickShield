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
    
    // Joystick Callbacks
    joystickShield.onJSUp(&up);
    joystickShield.onJSRightUp(&rightUp);
    joystickShield.onJSRight(&right);
    joystickShield.onJSRightDown(&rightDown);
    joystickShield.onJSDown(&down);
    joystickShield.onJSLeftDown(&leftDown);
    joystickShield.onJSLeft(&left);
    joystickShield.onJSLeftUp(&leftUp);
    joystickShield.onJSnotCenter(&notCenter);

    // Button Callbacks
    joystickShield.onJoystickButton(&joystickButton);
    joystickShield.onUpButton(&upButton);
    joystickShield.onRightButton(&rightButton);
    joystickShield.onDownButton(&downButton);
    joystickShield.onLeftButton(&leftButton);
    joystickShield.onFButton(&FButton);
    joystickShield.onEButton(&EButton);
}


void loop() {
    joystickShield.processCallbacks(); // you don't have do anything else
    delay(500);
}

/** Define Callback Function **/
void up() {
    Serial.println("Up from callback");
}

void rightUp() {
    Serial.println("Right Up from callback");
}

void right() {
    Serial.println("Right from callback");
}

void rightDown() {
    Serial.println("Right Down from callback");
}

void down() {
    Serial.println("Down from callback");
}

void leftDown() {
    Serial.println("Left Down from callback");
}

void left() {
    Serial.println("Left from callback");
}

void leftUp() {
    Serial.println("Left Up from callback");
}

void joystickButton() {
    Serial.println("Joystick from callback");
}

void upButton() {
    Serial.println("Up Button from callback");
}

void rightButton() {
    Serial.println("Right Button from callback");
}

void downButton() {
    Serial.println("Down Button from callback");
}

void leftButton() {
    Serial.println("Left Button from callback");
}

void FButton() {
    Serial.println("F Button from callback");
}

void EButton() {
    Serial.println("E Button from callback");
}

void notCenter() {
   Serial.println("Not Center from callback");
   // new position functions
   Serial.print("x ");	Serial.print(joystickShield.xAmplitude());Serial.print(" y ");Serial.println(joystickShield.yAmplitude());
}
