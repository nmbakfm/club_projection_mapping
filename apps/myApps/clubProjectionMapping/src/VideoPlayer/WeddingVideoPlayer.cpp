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

void WeddingVideoPlayer::setMessage(string _message){
    message = _message;
}

string WeddingVideoPlayer::getMessage(){
    return message;
}

void WeddingVideoPlayer::update(){
    ofVideoPlayer::update();
}

void WeddingVideoPlayer::setNamePosition(float _x, float _y){
    pos = ofPoint(_x, _y);
}

void WeddingVideoPlayer::setNamePosition(ofPoint _msg_pos){
    pos = _msg_pos;
}

ofPoint WeddingVideoPlayer::getNamePosition(){
    return pos;
}

void WeddingVideoPlayer::drawMovie(float _x, float _y, float _w, float _h){
    BaseVideoPlayer::draw(_x, _y, _w, _h);
    
    if (getCurrentFrame() > 609) {
        ofSetColor(0, 128);
        nameFont.drawStringAsShapes(message, pos.x - nameFont.stringWidth(message)/2+5, pos.y - nameFont.stringHeight(message)/2+130+3);
        ofSetColor(255);
        nameFont.drawStringAsShapes(message, pos.x - nameFont.stringWidth(message)/2, pos.y - nameFont.stringHeight(message)/2+130);
    }
}

void WeddingVideoPlayer::getIsMovieDone(){
    ofVideoPlayer::getIsMovieDone();
}