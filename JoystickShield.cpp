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

#include "JoystickShield.h"

/**
 * Constructor
 *
 */
JoystickShield::JoystickShield() {
    // define some threshold values. Change them if your Joystick is different
    setThreshold(510, 530, 510, 540);

    // Sparkfun Joystick shield connects the Joystick to Pins 0 and 1.
    // Change it if you are using a different shield
    setJoystickPins(0, 1);

    // Sparkfun Joystick shield connects the buttons to the following pins.
    // change it if you are using a different shield.
    setButtonPins(2, 4, 3, 5, 6);

    // by default set the position to centered
    currentStatus = CENTER;

    // by default set the button state to NO_BUTTON
    currentButton = NO_BUTTON;

    // initialize all callback function pointers to NULL
    initializeCallbacks();
}

/**
 * Set Analyog pins which are connected to the Joystick
 *
 */
void JoystickShield::setJoystickPins(byte pinX, byte pinY) {
    pin_analog_x = pinX;
    pin_analog_y = pinY;

    // set Joystick pins to input mode
    pinMode(pin_analog_x, INPUT);
    pinMode(pin_analog_y, INPUT);
}

/**
 * Set the pins used by the buttons
 *
 */
void JoystickShield::setButtonPins(byte pinSelect, byte pinUp, byte pinRight, byte pinDown, byte pinLeft) {
    pin_joystick_button = pinSelect;
    pin_up_button       = pinUp;
    pin_right_button    = pinRight;
    pin_down_button     = pinDown;
    pin_left_button     = pinLeft;

    // set Button pins to input mode
    pinMode(pin_joystick_button, INPUT);
    pinMode(pin_up_button      , INPUT);
    pinMode(pin_right_button   , INPUT);
    pinMode(pin_down_button    , INPUT);
    pinMode(pin_left_button    , INPUT);

    // Enable "pull-up resistors" for buttons
    digitalWrite(pin_joystick_button, HIGH);
    digitalWrite(pin_up_button      , HIGH);
    digitalWrite(pin_right_button   , HIGH);
    digitalWrite(pin_down_button    , HIGH);
    digitalWrite(pin_left_button    , HIGH);
}

/**
 * Configure threshold values for Joystick
 *
 */
void JoystickShield::setThreshold(int xLow, int xHigh, int yLow, int yHigh) {
    x_threshold_low  = xLow;
    x_threshold_high = xHigh;
    y_threshold_low  = yLow;
    y_threshold_high = yHigh;
}

/**
 * Process Events. This should be called in the loop()
 *
 */
void JoystickShield::processEvents() {
    int x_direction = 0;
    int y_direction = 0;

    // read from Joystick pins
    int x_position = analogRead(pin_analog_x);
    int y_position = analogRead(pin_analog_y);

    // determine Joystick direction
    if (x_position > x_threshold_high) {
        x_direction = 1;
    } else if (x_position < x_threshold_low) {
        x_direction = -1;
    }

    if (y_position > y_threshold_high) {
        y_direction = 1;
    } else if (y_position < y_threshold_low) {
        y_direction = -1;
    }

    if (x_direction == -1) {
        if (y_direction == -1) {
            currentStatus = LEFT_DOWN;
        } else if (y_direction == 0) {
            currentStatus = LEFT;
        } else {
            currentStatus = LEFT_UP;
        }
    } else if (x_direction == 0) {
        if (y_direction == -1) {
            currentStatus = DOWN;
        } else if (y_direction == 0) {
            currentStatus = CENTER;
        } else {
            currentStatus = UP;
        }
    } else {
        if (y_direction == -1) {
            currentStatus = RIGHT_DOWN;
        } else if (y_direction == 0) {
            currentStatus = RIGHT;
        } else {
            currentStatus = RIGHT_UP;
        }
    }

    // Determine which buttons were pressed
    if (digitalRead(pin_joystick_button) == LOW) {
        currentButton = JOYSTICK_BUTTON;
    }

    if (digitalRead(pin_up_button) == LOW) {
        currentButton = UP_BUTTON;
    }

    if (digitalRead(pin_right_button) == LOW) {
        currentButton = RIGHT_BUTTON;
    }

    if (digitalRead(pin_down_button) == LOW) {
        currentButton = DOWN_BUTTON;
    }

    if (digitalRead(pin_left_button) == LOW) {
        currentButton = LEFT_BUTTON;
    }

}


void JoystickShield::processCallbacks() {
    processEvents();

    // Joystick Callbacks
    if (isCenter() && centerCallback != NULL) {
        centerCallback();
    }

    if (isUp() && upCallback != NULL) {
        upCallback();
    }

    if (isRightUp() && rightUpCallback != NULL) {
        rightUpCallback();
    }

    if (isRight() && rightCallback != NULL) {
        rightCallback();
    }

    if (isRightDown() && rightDownCallback != NULL) {
        rightDownCallback();
    }

    if (isDown() && downCallback != NULL) {
        downCallback();
    }

    if (isLeftDown() && leftDownCallback != NULL) {
        leftDownCallback();
    }

    if (isLeft() && leftCallback != NULL) {
        leftCallback();
    }

    if (isLeftUp() && leftUpCallback != NULL) {
        leftUpCallback();
    }

    // Button Callbacks
    if (isJoystickButton() && jsButtonCallback != NULL) {
        jsButtonCallback();
    }

    if (isUpButton() && upButtonCallback != NULL) {
        upButtonCallback();
    }

    if (isRightButton() && rightButtonCallback != NULL) {
        rightButtonCallback();
    }

    if (isDownButton() && downButtonCallback != NULL) {
        downButtonCallback();
    }

    if (isLeftButton() && leftButtonCallback != NULL) {
        leftButtonCallback();
    }

}

/**
 * Joystick in Center status
 *
 */
bool JoystickShield::isCenter() {
    if (currentStatus == CENTER ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Up status
 *
 */
bool JoystickShield::isUp() {
    if (currentStatus == UP ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Right Up status
 *
 */
bool JoystickShield::isRightUp() {
    if (currentStatus == RIGHT_UP ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Right status
 *
 */
bool JoystickShield::isRight() {
    if (currentStatus == RIGHT ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Right Down status
 *
 */
bool JoystickShield::isRightDown() {
    if (currentStatus == RIGHT_DOWN ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Down status
 *
 */
bool JoystickShield::isDown() {
    if (currentStatus == DOWN ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Left Down status
 *
 */
bool JoystickShield::isLeftDown() {
    if (currentStatus == LEFT_DOWN ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Left status
 *
 */
bool JoystickShield::isLeft() {
    if (currentStatus == LEFT ) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick in Left Up status
 *
 */
bool JoystickShield::isLeftUp() {
    if (currentStatus == LEFT_UP) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick button pressed
 *
 */
bool JoystickShield::isJoystickButton() {
    if (currentButton == JOYSTICK_BUTTON) {
        clearButtonStates();
        return true;
    } else {
        return false;
    }
}

/**
 * Up button pressed
 *
 */
bool JoystickShield::isUpButton() {
    if (currentButton == UP_BUTTON) {
        clearButtonStates();
        return true;
    } else {
        return false;
    }
}

/**
 * Right button pressed
 *
 */
bool JoystickShield::isRightButton() {
    if (currentButton == RIGHT_BUTTON) {
        clearButtonStates();
        return true;
    } else {
        return false;
    }
}

/**
 * Down button pressed
 *
 */
bool JoystickShield::isDownButton() {
    if (currentButton == DOWN_BUTTON) {
        clearButtonStates();
        return true;
    } else {
        return false;
    }
}

/**
 * Left button pressed
 *
 */
bool JoystickShield::isLeftButton() {
    if (currentButton == LEFT_BUTTON) {
        clearButtonStates();
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick Callbacks
 *
 */
/****************************************************************** */
void JoystickShield::onJSCenter(void (*centerCallback)(void)) {
    this->centerCallback = centerCallback;
}

void JoystickShield::onJSUp(void (*upCallback)(void)) {
    this->upCallback = upCallback;
}

void JoystickShield::onJSRightUp(void (*rightUpCallback)(void)) {
    this->rightUpCallback = rightUpCallback;
}

void JoystickShield::onJSRight(void (*rightCallback)(void)) {
    this->rightCallback = rightCallback;
}

void JoystickShield::onJSRightDown(void (*rightDownCallback)(void)) {
    this->rightDownCallback = rightDownCallback;
}

void JoystickShield::onJSDown(void (*downCallback)(void)) {
    this->downCallback = downCallback;
}

void JoystickShield::onJSLeftDown(void (*leftDownCallback)(void)) {
    this->leftDownCallback = leftDownCallback;
}

void JoystickShield::onJSLeft(void (*leftCallback)(void)) {
    this->leftCallback = leftCallback;
}

void JoystickShield::onJSLeftUp(void (*leftUpCallback)(void)) {
    this->leftUpCallback = leftUpCallback;
}

/****************************************************************** */

/**
 * Button Callbacks
 *
 */
 /****************************************************************** */
void JoystickShield::onJoystickButton(void (*jsButtonCallback)(void)) {
    this->jsButtonCallback = jsButtonCallback;
}

void JoystickShield::onUpButton(void (*upButtonCallback)(void)) {
    this->upButtonCallback = upButtonCallback;
}

void JoystickShield::onRightButton(void (*rightButtonCallback)(void)) {
    this->rightButtonCallback = rightButtonCallback;
}

void JoystickShield::onDownButton(void (*downButtonCallback)(void)) {
    this->downButtonCallback = downButtonCallback;
}

void JoystickShield::onLeftButton(void (*leftButtonCallback)(void)) {
    this->leftButtonCallback = leftButtonCallback;
}

/****************************************************************** */

/**
 * Clear the current button state
 *
 */
void JoystickShield::clearButtonStates() {
    currentButton = NO_BUTTON;
}

/**
 * Initialize all Function pointers to NULL
 *
 */
void JoystickShield::initializeCallbacks() {
    // Joystick callbacks
    centerCallback      = NULL;
    upCallback          = NULL;
    rightUpCallback     = NULL;
    rightCallback       = NULL;
    rightDownCallback   = NULL;
    downCallback        = NULL;
    leftDownCallback    = NULL;
    leftCallback        = NULL;
    leftUpCallback      = NULL;

    // Button callbacks
    jsButtonCallback    = NULL;
    upButtonCallback    = NULL;
    rightButtonCallback = NULL;
    downButtonCallback  = NULL;
    leftButtonCallback  = NULL;
}
