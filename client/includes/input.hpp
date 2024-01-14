/**
 * @file input.hpp
 * @brief contains the structures for the actions, keybindings and states
 * @date 09-01-2024
 */

#pragma once

/**
 * @brief these actions describe the state of the abstracted actions
 */
enum Action{
    EMPTY,
    CLICK_PRESS,
    CLICK_RELEASE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOOT,
    EXIT,
    GOBACK,
    DEL,
    SPACE,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    DOT,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE
};

/**
 * @brief this struct contains the keybindings for the actions
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
    Action dotAction;
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

    void removeAction(Action& actionToRemove) {
        if (upAction == actionToRemove)
            upAction = EMPTY;
        if (downAction == actionToRemove)
            downAction = EMPTY;
        if (leftAction == actionToRemove)
            leftAction = EMPTY;
        if (rightAction == actionToRemove)
            rightAction = EMPTY;
        if (spaceAction == actionToRemove)
            spaceAction = EMPTY;
        if (aAction == actionToRemove)
            aAction = EMPTY;
        if (bAction == actionToRemove)
            bAction = EMPTY;
        if (cAction == actionToRemove)
            cAction = EMPTY;
        if (dAction == actionToRemove)
            dAction = EMPTY;
        if (eAction == actionToRemove)
            eAction = EMPTY;
        if (fAction == actionToRemove)
            fAction = EMPTY;
        if (gAction == actionToRemove)
            gAction = EMPTY;
        if (hAction == actionToRemove)
            hAction = EMPTY;
        if (iAction == actionToRemove)
            iAction = EMPTY;
        if (jAction == actionToRemove)
            jAction = EMPTY;
        if (kAction == actionToRemove)
            kAction = EMPTY;
        if (lAction == actionToRemove)
            lAction = EMPTY;
        if (mAction == actionToRemove)
            mAction = EMPTY;
        if (nAction == actionToRemove)
            nAction = EMPTY;
        if (oAction == actionToRemove)
            oAction = EMPTY;
        if (pAction == actionToRemove)
            pAction = EMPTY;
        if (qAction == actionToRemove)
            qAction = EMPTY;
        if (rAction == actionToRemove)
            rAction = EMPTY;
        if (sAction == actionToRemove)
            sAction = EMPTY;
        if (tAction == actionToRemove)
            tAction = EMPTY;
        if (uAction == actionToRemove)
            uAction = EMPTY;
        if (vAction == actionToRemove)
            vAction = EMPTY;
        if (wAction == actionToRemove)
            wAction = EMPTY;
        if (xAction == actionToRemove)
            xAction = EMPTY;
        if (yAction == actionToRemove)
            yAction = EMPTY;
        if (zAction == actionToRemove)
            zAction = EMPTY;
    }
};

/**
 * @brief Possible states of the mouse
 */
struct MouseState {
    int x;
    int y;
    bool left;
    bool right;
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
    bool dot;
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
