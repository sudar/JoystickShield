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

class JoystickShield {

public:

    JoystickShield(); // constructor

    void setPins (byte pinX, byte pinY);
    void setThreshold(int xLow, int xHigh, int yLow, int yHigh);

    void processEvents();
    void processCallbacks();

    bool isCentered();
    bool isUp();
    bool isRightUp();
    bool isRight();
    bool isRightDown();
    bool isDown();
    bool isLeftDown();
    bool isLeft();
    bool isLeftUp();

private:

    int x_threshold_low;
    int x_threshold_high;
    int y_threshold_low;
    int y_threshold_high;

    byte pin_analog_x;
    byte pin_analog_y;

    JoystickStates currentStatus;
};

#endif
