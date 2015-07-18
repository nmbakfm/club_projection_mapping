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
    endFrameCount = 0;
}

void BaseVideoPlayer::setNameFont(string _font_name, int _font_size){
    font_name = _font_name;
    font_size = _font_size;
    nameFont.load(_font_name, _font_size, true, true, true);
}

void BaseVideoPlayer::setCurrentVolume(float _curVol){
    curVol = _curVol;
};
