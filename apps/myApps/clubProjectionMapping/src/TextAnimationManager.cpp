//
//  TextAnimationManager.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#include "TextAnimationManager.hpp"

shared_ptr<TextAnimationManager> TextAnimationManager::_singleton;

void TextAnimationManager::draw(){
    if (drawer_queue.empty())return;
    drawer_queue.front()->draw();
}

void TextAnimationManager::clear(){
    while (!drawer_queue.empty()) {
        drawer_queue.pop();
    }
}

void TextAnimationManager::nextImidiate(){
    if (drawer_queue.empty())return;
    drawer_queue.pop();
}

void TextAnimationManager::update(){
    if (drawer_queue.empty())return;
    drawer_queue.front()->update();
    if (drawer_queue.front()->isDone()) {
        drawer_queue.pop();
    }
}

shared_ptr<TextDrawer> TextAnimationManager::setNext(shared_ptr<TextDrawer> drawer){
    this->drawer_queue.push(drawer);
    return drawer;
}