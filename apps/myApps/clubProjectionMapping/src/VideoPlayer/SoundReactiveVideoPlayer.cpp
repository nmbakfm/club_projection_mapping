//
//  SoundReactiveVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/07/16.
//
//

#include "SoundReactiveVideoPlayer.h"

#define FRAME_SMOOTHING_VAL 0

SoundReactivePlayer::SoundReactivePlayer(){
    frameCount = 0;
}

SoundReactivePlayer::SoundReactivePlayer(int _endFrameCount, float _soundSensitivity){
    frameCount = 0;
    endFrameCount = _endFrameCount;
    soundSensitivity = _soundSensitivity;
    currentFrame = 0;
}

void SoundReactivePlayer::drawMovie(float _x, float _y, float _w, float _h){
    draw(_x, _y, _w, _h);
//    ofBackground(ofMap(curVol, 0, soundSensitivity, 0, 1, false)*255);
}

void SoundReactivePlayer::updateFrame(){
//    setPaused(true);
    update();
    float curVol = this->getCurrentVolume();
    float target_pct = ofMap(curVol, 0, soundSensitivity, 0, 1, false);
    
    cout << "targetFrame:" << target_pct << endl;
    cout << "curVol:\t" << curVol << endl;
    setPosition(target_pct);
    ++ frameCount;
}

bool SoundReactivePlayer::isMovieDone(){
    return frameCount > endFrameCount;
}