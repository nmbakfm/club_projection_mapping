//
//  BaseVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#include "BaseVideoPlayer.h"

string BaseVideoPlayer::font_name;
int BaseVideoPlayer::font_size;
ofTrueTypeFont BaseVideoPlayer::nameFont;

BaseVideoPlayer::BaseVideoPlayer(){
    
}

void BaseVideoPlayer::setNameFont(string _font_name, int _font_size){
    nameFont = ofTrueTypeFont();
    font_name = _font_name;
    font_size = _font_size;
    nameFont.load(_font_name, _font_size, true, true, true);
}

void BaseVideoPlayer::update(){
    ofVideoPlayer::update();
}

void BaseVideoPlayer::draw(float _x, float _y, float _w, float _h){
    ofVideoPlayer::draw(_x, _y, _w, _h);
}