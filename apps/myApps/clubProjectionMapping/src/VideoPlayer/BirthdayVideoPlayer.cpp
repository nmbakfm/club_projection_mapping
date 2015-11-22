//
//  BirthdayVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#include "BirthdayVideoPlayer.h"

BirthdayVideoPlayer::BirthdayVideoPlayer(){
    
}

void BirthdayVideoPlayer::updateFrame(){
    update();
}

void BirthdayVideoPlayer::drawMovie(float _x, float _y, float _w, float _h){
    draw(_x, _y, _w, _h);
    
    string message = this->getMessage();
    ofPoint pos = this->getPosition();
    
    if (getCurrentFrame() > 522) {
        ofSetColor(255);
        Settings::birthdayFont->drawStringAsShapes(message, pos.x - Settings::birthdayFont->stringWidth(message)/2, pos.y - Settings::birthdayFont->stringHeight(message)/2+130);
    }
}