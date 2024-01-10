/**
 * @file actions.hpp
 * @brief contains the structures for the actions, keybindings and states
 * @date 09-01-2024
 */

#pragma once

/**
 * @brief 
 * these actions describe the state of the abstracted actions
 */
enum Action{
    EMPTY,
    CLICK_PRESS,
    CLICK_RELEASE,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOOT,
    EXIT
};

/**
 * @brief 
 * this struct contains the keybindings for the actions
 */
struct KeyBinding {
    Action lClickPressAction;
    Action rClickPressAction;
    Action upAction;
    Action downAction;
    Action leftAction;
    Action rightAction;
    Action spaceAction;
    Action shiftAction;
    Action ctrlAction;
    Action altAction;
    Action enterAction;
    Action escapeAction;
    Action tabAction;
    Action backspaceAction;
    Action aAction;
    Action bAction;
    Action cAction;
    Action dAction;
    Action eAction;
    Action fAction;
    Action gAction;
    Action hAction;
    Action iAction;
    Action jAction;
    Action kAction;
    Action lAction;
    Action mAction;
    Action nAction;
    Action oAction;
    Action pAction;
    Action qAction;
    Action rAction;
    Action sAction;
    Action tAction;
    Action uAction;
    Action vAction;
    Action wAction;
    Action xAction;
    Action yAction;
    Action zAction;
    Action zeroAction;
    Action oneAction;
    Action twoAction;
    Action threeAction;
    Action fourAction;
    Action fiveAction;
    Action sixAction;
    Action sevenAction;
    Action eightAction;
    Action nineAction;
};

struct MouseState {
    int x;
    int y;
    bool left_pressed;
    bool right_pressed;
    bool left_released;
    bool right_released;
};

/**
 * @brief these Keystates describe the state of the keys on the keyboard
 */
struct KeyState {
    MouseState mouse;
    bool up;
    bool down;
    bool left;
    bool right;
    bool space;
    bool shift;
    bool ctrl;
    bool alt;
    bool enter;
    bool escape;
    bool tab;
    bool backspace;
    bool a;
    bool b;
    bool c;
    bool d;
    bool e;
    bool f;
    bool g;
    bool h;
    bool i;
    bool j;
    bool k;
    bool l;
    bool m;
    bool n;
    bool o;
    bool p;
    bool q;
    bool r;
    bool s;
    bool t;
    bool u;
    bool v;
    bool w;
    bool x;
    bool y;
    bool z;
    bool zero;
    bool one;
    bool two;
    bool three;
    bool four;
    bool five;
    bool six;
    bool seven;
    bool eight;
    bool nine;
};
