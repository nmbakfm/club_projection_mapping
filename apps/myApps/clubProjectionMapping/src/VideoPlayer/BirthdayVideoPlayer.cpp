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

void BirthdayVideoPlayer::setMessage(string _message){
    message = _message;
}

string BirthdayVideoPlayer::getMessage(){
    return message;
}

void BirthdayVideoPlayer::update(){
    ofVideoPlayer::update();
}

void BirthdayVideoPlayer::setNamePosition(float _x, float _y){
    pos = ofPoint(_x, _y);
}

void BirthdayVideoPlayer::setNamePosition(ofPoint _msg_pos){
    pos = _msg_pos;
}

ofPoint BirthdayVideoPlayer::getNamePosition(){
    return pos;
}

void BirthdayVideoPlayer::drawMovie(float _x, float _y, float _w, float _h){
    draw(_x, _y, _w, _h);
    
    if (getCurrentFrame() > 522) {
        ofSetColor(255);
        nameFont.drawStringAsShapes(message, pos.x - nameFont.stringWidth(message)/2, pos.y - nameFont.stringHeight(message)/2+130);
    }
}

bool BirthdayVideoPlayer::getIsMovieDone(){
    ofVideoPlayer::getIsMovieDone();
}