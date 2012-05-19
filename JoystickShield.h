/**
   JoystickShield - Arduino Library for JoystickShield (http://sudarmuthu.com/arduino/joystickshield)

 *
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <sudar@sudarmuthu.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer or coffee in return - Sudar
 * ----------------------------------------------------------------------------
 */

#ifndef JoystickShield_H
#define JoystickShield_H

// Compatibility for Arduino 1.0

#if ARDUINO >= 100
    #include <Arduino.h>
#else    
    #include <WProgram.h>
#endif

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
