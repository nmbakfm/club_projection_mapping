//
//  NormalVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#include "NormalVideoPlayer.h"

void NormalVideoPlayer::drawMovie(float _x, float _y, float _w, float _h) {
    draw(_x, _y, _w, _h);
    
    string message = this->getMessage();
    ofPoint pos = this->getPosition();
    
    if(this->hasMessage()){
        ofSetColor(255);
        Settings::birthdayFont->drawStringAsShapes(message, pos.x - Settings::birthdayFont->stringWidth(message)/2, pos.y - Settings::birthdayFont->stringHeight(message)/2+130);
    }
};

