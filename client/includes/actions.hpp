/**
 * @file actions.hpp
 * @brief contains the Actions struct
 * @date 09-01-2024
 */

#pragma once

/**
 * @brief 
 * these actions describe the state of the abstracted actions
 */
enum Action{
    EMPTY,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOOT,
};

/**
 * @brief 
 * this struct contains the keybindings for the actions
 */
struct KeyBinding {
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
