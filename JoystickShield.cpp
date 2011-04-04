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
    pin_select_button = pinSelect;
    pin_up_button     = pinUp;
    pin_right_button  = pinRight;
    pin_down_button   = pinDown;
    pin_left_button   = pinLeft;

    // set Button pins to input mode
    pinMode(pin_select_button, INPUT);
    pinMode(pin_up_button    , INPUT);
    pinMode(pin_right_button , INPUT);
    pinMode(pin_down_button  , INPUT);
    pinMode(pin_left_button  , INPUT);

    // Enable "pull-up resistors" for buttons
    digitalWrite(pin_select_button, HIGH);
    digitalWrite(pin_up_button    , HIGH);
    digitalWrite(pin_right_button , HIGH);
    digitalWrite(pin_down_button  , HIGH);
    digitalWrite(pin_left_button  , HIGH);
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
    if (digitalRead(pin_select_button) == LOW) {
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

/**
 * Joystick in Center status
 *
 */
bool JoystickShield::isCentered() {
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
 * Clear the current button state
 *
 */
void JoystickShield::clearButtonStates() {
    currentButton = NO_BUTTON;
}
