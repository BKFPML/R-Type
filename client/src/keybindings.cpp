/**
 * @file keybindings.cpp
 * @brief contains the functions related to keybindings
 * @date 09-01-2024
 */

#pragma once

#include "../includes/actions.hpp"
#include "../includes/client.hpp"

/**
 * @brief reset all keybinds to default setting
 * 
 * @return KeyBinding 
 */
KeyBinding defaultKeyBindings() {
    return {
        MOVE_UP,    // upAction
        MOVE_DOWN,  // downAction
        MOVE_LEFT,  // leftAction
        MOVE_RIGHT, // rightAction
        SHOOT,      // spaceAction
        EMPTY,      //shiftAction
        EMPTY,      //ctrlAction
        EMPTY,      //altAction
        SHOOT,      //enterAction
        EMPTY,      //escapeAction
        EMPTY,      //tabAction
        EMPTY,      //backspaceAction
        MOVE_LEFT,  //aAction
        EMPTY,      //bAction
        EMPTY,      //cAction
        MOVE_RIGHT, //dAction
        EMPTY,      //eAction
        EMPTY,      //fAction
        EMPTY,      //gAction
        EMPTY,      //hAction
        EMPTY,      //iAction
        EMPTY,      //jAction
        EMPTY,      //kAction
        EMPTY,      //lAction
        EMPTY,      //mAction
        EMPTY,      //nAction
        EMPTY,      //oAction
        EMPTY,      //pAction
        EMPTY,      //qAction
        EMPTY,      //rAction
        MOVE_DOWN,  //sAction
        EMPTY,      //tAction
        EMPTY,      //uAction
        EMPTY,      //vAction
        MOVE_UP,    //wAction
        EMPTY,      //xAction
        EMPTY,      //yAction
        EMPTY,      //zAction
        EMPTY,      //zeroAction
        EMPTY,      //oneAction
        EMPTY,      //twoAction
        EMPTY,      //threeAction
        EMPTY,      //fourAction
        EMPTY,      //fiveAction
        EMPTY,      //sixAction
        EMPTY,      //sevenAction
        EMPTY,      //eightAction
        EMPTY,      //nineAction
    };
}
