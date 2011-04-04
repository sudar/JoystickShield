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
    bool isCentered();
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
    byte pin_select_button;
    byte pin_up_button;
    byte pin_right_button;
    byte pin_down_button;
    byte pin_left_button;

    //current states of Joystick
    JoystickStates currentStatus;

    //current button states
    ButtonStates currentButton;

    void clearButtonStates();
};

#endif
