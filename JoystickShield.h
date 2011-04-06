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

#ifndef JoystickShield_H
#define JoystickShield_H

#include <WProgram.h>

/**
 * Enum to hold the different states of the Joystick
 *
 */
enum JoystickStates {
    CENTER,  // 0
    UP,
    RIGHT_UP,
    RIGHT,
    RIGHT_DOWN,
    DOWN,
    LEFT_DOWN,
    LEFT,
    LEFT_UP   //8
};

/**
 * Enum to hold the button states
 *
 */
enum ButtonStates {
    NO_BUTTON,     //0
    JOYSTICK_BUTTON,
    UP_BUTTON,
    RIGHT_BUTTON,
    DOWN_BUTTON,
    LEFT_BUTTON    //5
};

/**
 * Class to encapsulate JoystickShield
 */
class JoystickShield {

public:

    JoystickShield(); // constructor

    void setJoystickPins (byte pinX, byte pinY);
    void setButtonPins(byte pinSelect, byte pinUp, byte pinRight, byte pinDown, byte pinLeft);
    void setThreshold(int xLow, int xHigh, int yLow, int yHigh);

    void processEvents();
    void processCallbacks();

    // Joystick events
    bool isCenter();
    bool isUp();
    bool isRightUp();
    bool isRight();
    bool isRightDown();
    bool isDown();
    bool isLeftDown();
    bool isLeft();
    bool isLeftUp();

    // Button events
    bool isJoystickButton();
    bool isUpButton();
    bool isRightButton();
    bool isDownButton();
    bool isLeftButton();

    // Joystick callbacks
    void onJSCenter(void (*centerCallback)(void));
    void onJSUp(void (*upCallback)(void));
    void onJSRightUp(void (*rightUpCallback)(void));
    void onJSRight(void (*rightCallback)(void));
    void onJSRightDown(void (*rightDownCallback)(void));
    void onJSDown(void (*downCallback)(void));
    void onJSLeftDown(void (*leftDownCallback)(void));
    void onJSLeft(void (*leftCallback)(void));
    void onJSLeftUp(void (*leftUpCallback)(void));

    // Button callbacks
    void onJoystickButton(void (*jsButtonCallback)(void));
    void onUpButton(void (*upButtonCallback)(void));
    void onRightButton(void (*rightButtonCallback)(void));
    void onDownButton(void (*downButtonCallback)(void));
    void onLeftButton(void (*leftButtonCallback)(void));

private:

    // threshold values
    int x_threshold_low;
    int x_threshold_high;
    int y_threshold_low;
    int y_threshold_high;

    // joystick pins
    byte pin_analog_x;
    byte pin_analog_y;

    //button pins
    byte pin_joystick_button;
    byte pin_up_button;
    byte pin_right_button;
    byte pin_down_button;
    byte pin_left_button;

    //current states of Joystick
    JoystickStates currentStatus;

    //current button states
    ButtonStates currentButton;

    // Joystick callbacks
    void (*centerCallback)(void);
    void (*upCallback)(void);
    void (*rightUpCallback)(void);
    void (*rightCallback)(void);
    void (*rightDownCallback)(void);
    void (*downCallback)(void);
    void (*leftDownCallback)(void);
    void (*leftCallback)(void);
    void (*leftUpCallback)(void);

    // Button callbacks
    void (*jsButtonCallback)(void);
    void (*upButtonCallback)(void);
    void (*rightButtonCallback)(void);
    void (*downButtonCallback)(void);
    void (*leftButtonCallback)(void);

    // helper functions
    void clearButtonStates();
    void initializeCallbacks();
};

#endif
