/**
   JoystickShield - Arduino Library for JoystickShield (http://hardwarefun.com/projects/joystick-shield)

 *
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

#ifndef JoystickShield_H
#define JoystickShield_H

#define CENTERTOLERANCE 5

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
    LEFT_BUTTON,    //5
	F_BUTTON,
	E_BUTTON
};

/**
 * Class to encapsulate JoystickShield
 */
class JoystickShield {

public:

    JoystickShield(); // constructor

    void setJoystickPins (byte pinX, byte pinY);
    void setButtonPins(byte pinSelect, byte pinUp, byte pinRight, byte pinDown, byte pinLeft, byte pinF, byte pinE);
    void setThreshold(int xLow, int xHigh, int yLow, int yHigh);

    void processEvents();
    void processCallbacks();
	
	void calibrateJoystick();

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
	bool isNotCenter();
	
	// Joystick coordinates
	int xAmplitude();
	int yAmplitude();

    // Button events
    bool isJoystickButton();
    bool isUpButton();
    bool isRightButton();
    bool isDownButton();
    bool isLeftButton();
	bool isFButton();
	bool isEButton();

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
	void onJSnotCenter(void (*notCenterCallback)(void));

    // Button callbacks
    void onJoystickButton(void (*jsButtonCallback)(void));
    void onUpButton(void (*upButtonCallback)(void));
    void onRightButton(void (*rightButtonCallback)(void));
    void onDownButton(void (*downButtonCallback)(void));
    void onLeftButton(void (*leftButtonCallback)(void));
	void onFButton(void (*FButtonCallback)(void));
	void onEButton(void (*EButtonCallback)(void));
	
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
	byte pin_F_button;
	byte pin_E_button;
	
	// joystick
	byte joystikStroke;
	int x_position;
	int y_position;

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
	void (*notCenterCallback)(void);

    // Button callbacks
    void (*jsButtonCallback)(void);
    void (*upButtonCallback)(void);
    void (*rightButtonCallback)(void);
    void (*downButtonCallback)(void);
    void (*leftButtonCallback)(void);
	void (*FButtonCallback)(void);
	void (*EButtonCallback)(void);
	

    // helper functions
    void clearButtonStates();
    void initializeCallbacks();
};

#endif
