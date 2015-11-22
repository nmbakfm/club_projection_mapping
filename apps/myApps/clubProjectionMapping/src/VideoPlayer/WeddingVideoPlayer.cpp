//
//  WeddingVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/07/09.
//
//

#include "WeddingVideoPlayer.h"

WeddingVideoPlayer::WeddingVideoPlayer(){
    
}

void WeddingVideoPlayer::updateFrame(){
    update();
}

void WeddingVideoPlayer::drawMovie(float _x, float _y, float _w, float _h){
    draw(_x, _y, _w, _h);
    string message = this->getMessage();
    ofPoint pos = this->getMessagePosition();
    
    if (getCurrentFrame() > 609) {
        ofSetColor(0, 128);
        Settings::weddingFont->drawStringAsShapes(message, pos.x - Settings::weddingFont->stringWidth(message)/2+5, pos.y - Settings::weddingFont->stringHeight(message)/2+130+3);
        ofSetColor(255);
        Settings::weddingFont->drawStringAsShapes(message, pos.x - Settings::weddingFont->stringWidth(message)/2, pos.y - Settings::weddingFont->stringHeight(message)/2+130);
    }
}