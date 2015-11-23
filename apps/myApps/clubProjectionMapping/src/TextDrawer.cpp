//
//  TextDrawer.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#include "TextDrawer.hpp"
#include "Settings.h"

std::shared_ptr<TextDrawer> TextDrawer::Alloc(){
    auto p = std::shared_ptr<TextDrawer>(new TextDrawer());
    p->self = p;
    p->setPosition(ofPoint(0,0));
    return p;
}

shared_ptr<ofTrueTypeFont> TextDrawer::getTrueTypeFont(){
    switch (this->fontType){
        case NormalFontType:
            return Settings::normalFont;
            break;
        case WeddingFontType:
            return Settings::weddingFont;
            break;
        case BirthdayFontType:
            return Settings::birthdayFont;
            break;
    }
    return Settings::normalFont;
}

void TextDrawer::draw(){
    ofPoint pos =  position;
    ofSetColor(0, 128);
    auto font = getTrueTypeFont();
    
    font->drawStringAsShapes(message, pos.x - font->stringWidth(message)/2+5, pos.y - font->stringHeight(message)/2+130 + 3);
    ofSetColor(255);
    font->drawStringAsShapes(message, pos.x - font->stringWidth(message)/2, pos.y - font->stringHeight(message)/2+130);
}

void TextDrawer::update(){
    if(!this->isDone())this->currentFrame ++;
}

bool TextDrawer::isDone(){
    return this->currentFrame >= this->showEndFrame;
}

void TextDrawer::restart(){
    this->currentFrame = 0;
}