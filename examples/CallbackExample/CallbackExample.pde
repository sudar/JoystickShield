#include <JoystickShield.h> // include JoystickShield Library

JoystickShield joystickShield; // create an instance of JoystickShield object

void setup() {
    Serial.begin(9600);

    // Joystick Callbacks
    joystickShield.onJSUp(&up);
    joystickShield.onJSRightUp(&rightUp);
    joystickShield.onJSRight(&right);
    joystickShield.onJSRightDown(&rightDown);
    joystickShield.onJSDown(&down);
    joystickShield.onJSLeftDown(&leftDown);
    joystickShield.onJSLeft(&left);
    joystickShield.onJSLeftUp(&leftUp);

    // Button Callbacks
    joystickShield.onJoystickButton(&joystickButton);
    joystickShield.onUpButton(&upButton);
    joystickShield.onRightButton(&rightButton);
    joystickShield.onDownButton(&downButton);
    joystickShield.onLeftButton(&leftButton);
}

void loop() {
    joystickShield.processCallbacks(); // you don't have do anything else
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
