/**
 * @file inputs.cpp
 * @brief Implementation of the inputs handling
 * @date 09-01-2024
 */

#include "../includes/client.hpp"

/**
 * @brief perform the set actions
 * 
 * @param action 
 */
void rtype::Client::performAction(Action action) {
    switch (action) {
        case EMPTY:
            break;
        case CLICK:
            if (_keys.mouse.left) std::cout << "Left click" << std::endl;
            if (_keys.mouse.right) std::cout << "Right click" << std::endl;
            std::cout << "x: " << _keys.mouse.x << " y: " << _keys.mouse.y << std::endl;
        case MOVE_UP:
            std::cout << "Move up" << std::endl;
            break;
        case MOVE_DOWN:
            std::cout << "Move down" << std::endl;
            break;
        case MOVE_LEFT:
            std::cout << "Move left" << std::endl;
            break;
        case MOVE_RIGHT:
            std::cout << "Move right" << std::endl;
            break;
        case SHOOT:
            std::cout << "Shoot" << std::endl;
            break;
        std::cout << "Unknown action" << std::endl;
    }
}

/**
 * @brief returns default keybinds
 * 
 * @return KeyBinding keybinds
 */
KeyBinding defaultKeyBindings() {
    return {
        CLICK,      // lClickAction
        CLICK,      // rClickAction
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

/**
 * @brief reset all keybinds to default setting
 * 
 */
void rtype::Client::resetKeyBindings() {
    _keyBindings = defaultKeyBindings();
}

/**
 * @brief maps the keys to the actions
 * 
 */
void rtype::Client::handleInput() {
    KeyState keys = _keys;
    KeyBinding keyBindings = _keyBindings;
    if(keys.mouse.left) performAction(keyBindings.lClickAction);
    if(keys.mouse.right) performAction(keyBindings.rClickAction);
    if (keys.up) performAction(keyBindings.upAction);
    if (keys.down) performAction(keyBindings.downAction);
    if (keys.left) performAction(keyBindings.leftAction);
    if (keys.right) performAction(keyBindings.rightAction);
    if (keys.space) performAction(keyBindings.spaceAction);
    if (keys.shift) performAction(keyBindings.shiftAction);
    if (keys.ctrl) performAction(keyBindings.ctrlAction);
    if (keys.alt) performAction(keyBindings.altAction);
    if (keys.enter) performAction(keyBindings.enterAction);
    if (keys.escape) performAction(keyBindings.escapeAction);
    if (keys.tab) performAction(keyBindings.tabAction);
    if (keys.backspace) performAction(keyBindings.backspaceAction);
    if (keys.a) performAction(keyBindings.aAction);
    if (keys.b) performAction(keyBindings.bAction);
    if (keys.c) performAction(keyBindings.cAction);
    if (keys.d) performAction(keyBindings.dAction);
    if (keys.e) performAction(keyBindings.eAction);
    if (keys.f) performAction(keyBindings.fAction);
    if (keys.g) performAction(keyBindings.gAction);
    if (keys.h) performAction(keyBindings.hAction);
    if (keys.i) performAction(keyBindings.iAction);
    if (keys.j) performAction(keyBindings.jAction);
    if (keys.k) performAction(keyBindings.kAction);
    if (keys.l) performAction(keyBindings.lAction);
    if (keys.m) performAction(keyBindings.mAction);
    if (keys.n) performAction(keyBindings.nAction);
    if (keys.o) performAction(keyBindings.oAction);
    if (keys.p) performAction(keyBindings.pAction);
    if (keys.q) performAction(keyBindings.qAction);
    if (keys.r) performAction(keyBindings.rAction);
    if (keys.s) performAction(keyBindings.sAction);
    if (keys.t) performAction(keyBindings.tAction);
    if (keys.u) performAction(keyBindings.uAction);
    if (keys.v) performAction(keyBindings.vAction);
    if (keys.w) performAction(keyBindings.wAction);
    if (keys.x) performAction(keyBindings.xAction);
    if (keys.y) performAction(keyBindings.yAction);
    if (keys.z) performAction(keyBindings.zAction);
    if (keys.zero) performAction(keyBindings.zeroAction);
    if (keys.one) performAction(keyBindings.oneAction);
    if (keys.two) performAction(keyBindings.twoAction);
    if (keys.three) performAction(keyBindings.threeAction);
    if (keys.four) performAction(keyBindings.fourAction);
    if (keys.five) performAction(keyBindings.fiveAction);
    if (keys.six) performAction(keyBindings.sixAction);
    if (keys.seven) performAction(keyBindings.sevenAction);
    if (keys.eight) performAction(keyBindings.eightAction);
    if (keys.nine) performAction(keyBindings.nineAction);
}
