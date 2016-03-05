/**
   JoystickShield - Arduino Library for JoystickShield (http://hardwarefun.com/projects/joystick-shield)

   Copyright 2011  Sudar Muthu  (email : sudar@sudarmuthu.com)
 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <sudar@sudarmuthu.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer or coffee in return - Sudar
 * ----------------------------------------------------------------------------
  * 2014 edit by Markus Mücke, muecke.ma(a)gmail.com
  * Changes for JoystickShield V1.2
  * added a function to read the amplitude of the joystick
  * added a auto calibrate function for 3.3V and 5V mode
  *
  * Added functions:
  *  Functions for F and E Button
  *  Calibrate Joystick
  *  xAmplitude
  *  yAmplitude
   *
   * 20th October 2015 edit by Lindsay Ward, https://github.com/lindsaymarkward
   * made buttons not mutually exclusive
   * functions report the current state button so multiple buttons can be pressed at one time
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
    setButtonPins(8, 2, 3, 4, 5, 7, 6);

    // by default set the position to centered
    currentStatus = CENTER;
    
    // initialize the button states array to all buttons not pressed
    memcpy(buttonStates, ALL_BUTTONS_OFF, sizeof(ALL_BUTTONS_OFF));

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
 * to deactivate a button use a pin outside of the range of the arduino e.g. 255
 */
void JoystickShield::setButtonPins(byte pinSelect, byte pinUp, byte pinRight, byte pinDown, byte pinLeft, byte pinF, byte pinE)  {
    pin_joystick_button = pinSelect;
    pin_up_button       = pinUp;
    pin_right_button    = pinRight;
    pin_down_button     = pinDown;
    pin_left_button     = pinLeft;
	pin_F_button		= pinF;
	pin_E_button		= pinE;

    // set Button pins to input mode
    pinMode(pin_joystick_button, INPUT);
    pinMode(pin_up_button      , INPUT);
    pinMode(pin_right_button   , INPUT);
    pinMode(pin_down_button    , INPUT);
    pinMode(pin_left_button    , INPUT);
	pinMode(pin_E_button	   , INPUT);
	pinMode(pin_F_button       , INPUT);

	// buttons use pull-up resistors by default
	setButtonPinsUnpressedState(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);
}

/**
 * Configure if the input from an unpressed button is HIGH or LOW.
 * This will enable a pull-up or a pull-down resistor for the pin of the button correspondingly.
 */
void JoystickShield::setButtonPinsUnpressedState(byte pinSelect, byte pinUp, byte pinRight, byte pinDown, byte pinLeft, byte pinF, byte pinE) {
	// store unpressed states
	pin_joystick_button_unpressed = pinSelect ? HIGH : LOW;
	pin_up_button_unpressed       = pinUp     ? HIGH : LOW;
	pin_right_button_unpressed    = pinRight  ? HIGH : LOW;
	pin_down_button_unpressed     = pinDown   ? HIGH : LOW;
	pin_left_button_unpressed     = pinLeft   ? HIGH : LOW;
	pin_F_button_unpressed        = pinF      ? HIGH : LOW;
	pin_E_button_unpressed        = pinE      ? HIGH : LOW;

	// Enable pull-up or pull-down resistors for buttons
	digitalWrite(pin_joystick_button, pin_joystick_button_unpressed);
	digitalWrite(pin_up_button      , pin_up_button_unpressed      );
	digitalWrite(pin_right_button   , pin_right_button_unpressed   );
	digitalWrite(pin_down_button    , pin_down_button_unpressed    );
	digitalWrite(pin_left_button    , pin_left_button_unpressed    );
	digitalWrite(pin_F_button       , pin_F_button_unpressed       );
	digitalWrite(pin_E_button       , pin_E_button_unpressed       );
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
 * Calibrate Joystick
 *
 */
void JoystickShield::calibrateJoystick()  {
	byte i;

	// calibrate x
	int xCenter = 0;
	for(i = 0; i<10; i++)
		xCenter += analogRead(pin_analog_x);
	xCenter /= i;

	// calibrate y
	int yCenter = 0;
	for(i = 0; i<10; i++)
		yCenter += analogRead(pin_analog_y);
	yCenter /= i;

	// save Stroke of Joystick
	joystickStroke = max(pin_analog_x, pin_analog_y)*1.01;

	// set Center with tolerance
	setThreshold(xCenter-CENTERTOLERANCE, xCenter+CENTERTOLERANCE, yCenter-CENTERTOLERANCE, yCenter+CENTERTOLERANCE);
}

/**
 * Process Events. This should be called in the loop()
 *
 */
void JoystickShield::processEvents() {
    int x_direction = 0;
    int y_direction = 0;

    // read from Joystick pins
    x_position = analogRead(pin_analog_x);
    y_position = analogRead(pin_analog_y);

    // determine Joystick direction
    if (x_position > x_threshold_high) {
        x_direction = 1;
		x_position = map(x_position, x_threshold_high,x_threshold_high+x_threshold_low,0,100);
		x_position = constrain(x_position,0,100);
	} else if (x_position < x_threshold_low) {
        x_direction = -1;
		x_position = map(x_position, 0,x_threshold_low,-100,0);
    } else
		x_position = 0;

    if (y_position > y_threshold_high) {
        y_direction = 1;
		y_position = map(y_position, y_threshold_high,y_threshold_high+y_threshold_low,0,100);
		y_position = constrain(y_position,0,100);
    } else if (y_position < y_threshold_low) {
        y_direction = -1;
		y_position = map(y_position, 0,y_threshold_low,-100,0);
    } else
		y_position = 0;
		

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
	
    // Determine which buttons were pressed, set button states array values to true/false accordingly
	buttonStates[0] = digitalRead(pin_up_button)       != pin_up_button_unpressed;
	buttonStates[1] = digitalRead(pin_right_button)    != pin_right_button_unpressed;
	buttonStates[2] = digitalRead(pin_down_button)     != pin_down_button_unpressed;
	buttonStates[3] = digitalRead(pin_left_button)     != pin_left_button_unpressed;
	buttonStates[4] = digitalRead(pin_E_button)        != pin_E_button_unpressed;
	buttonStates[5] = digitalRead(pin_F_button)        != pin_F_button_unpressed;
	buttonStates[6] = digitalRead(pin_joystick_button) != pin_joystick_button_unpressed;
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
	
	if (isNotCenter() && notCenterCallback != NULL) {
		notCenterCallback();
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
	
	if (isFButton() && FButtonCallback != NULL) {
        FButtonCallback();
    }
	
	if (isEButton() && EButtonCallback != NULL) {
		EButtonCallback();
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
 * Joystick in not Center status
 *
 */
bool JoystickShield::isNotCenter() {
    if (currentStatus != CENTER) {
        return true;
    } else {
        return false;
    }
}

/**
 * Joystick x position from -100 to 100, 0 = center
 *
 */
int JoystickShield::xAmplitude()  {
	return x_position;
}

/**
 * Joystick y position from -100 to 100, 0 = center
 *
 */
int JoystickShield::yAmplitude()  {
	return y_position;
}

/**
 * Up button pressed
 *
 */
bool JoystickShield::isUpButton() {
    return buttonStates[0];
}

/**
 * Right button pressed
 *
 */
bool JoystickShield::isRightButton() {
    return buttonStates[1];
}

/**
 * Down button pressed
 *
 */
bool JoystickShield::isDownButton() {
    return buttonStates[2];
}

/**
 * Left button pressed
 *
 */
bool JoystickShield::isLeftButton() {
    return buttonStates[3];
}

/**
 * E button pressed
 *
 */
bool JoystickShield::isEButton() {
    return buttonStates[4];
}

/**
 * F button pressed
 *
 */
bool JoystickShield::isFButton() {
    return buttonStates[5];
}

/**
 * Joystick button pressed
 *
 */
bool JoystickShield::isJoystickButton() {
    return buttonStates[6];
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

void JoystickShield::onJSnotCenter(void (*notCenterCallback)(void)) {
	this->notCenterCallback = notCenterCallback;
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

void JoystickShield::onFButton(void (*FButtonCallback)(void)) {
	this->FButtonCallback = FButtonCallback;
}

void JoystickShield::onEButton(void (*EButtonCallback)(void)) {
	this->EButtonCallback = EButtonCallback;
}

/****************************************************************** */

/**
 * Initialize all function pointers to NULL
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
	notCenterCallback   = NULL;

    // Button callbacks
    jsButtonCallback    = NULL;
    upButtonCallback    = NULL;
    rightButtonCallback = NULL;
    downButtonCallback  = NULL;
    leftButtonCallback  = NULL;
	FButtonCallback		= NULL;
	EButtonCallback		= NULL;
}
