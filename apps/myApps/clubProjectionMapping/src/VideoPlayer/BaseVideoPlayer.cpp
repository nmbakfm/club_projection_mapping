//
//  BaseVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#include "BaseVideoPlayer.h"

ofTrueTypeFont BaseVideoPlayer::weddingNameFont;
ofTrueTypeFont BaseVideoPlayer::birthdayNameFont;

BaseVideoPlayer::BaseVideoPlayer(){}

void BaseVideoPlayer::setNameFont(string _font_name, int _font_size){
    birthdayNameFont.load("font/NuevaStd-Bold.otf", 72, true, true, true);
    weddingNameFont.load("font/exmouth_.ttf", 72, true, true, true);
}

