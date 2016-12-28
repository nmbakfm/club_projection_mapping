//
//  SoundReactiveVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/07/16.
//
//

#include "SoundReactiveVideoPlayer.h"
#include "SoundReactiveDataSetManager.hpp"

#define FRAME_SMOOTHING_VAL 0

float SoundReactivePlayer::soFarMax = 0;

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
    //draw(_x, _y, _w, _h);
    auto&& data = SoundRactiveDataManager::datas.at(getMoviePath());
    if(data.size() == 0 )return;
    if(currentFrame >= data.size())currentFrame = data.size() - 1;
    data[currentFrame].draw(0, 0, Settings::movieWidth, Settings::movieHeight);
    //cout << data[currentFrame].getTextureData().textureID << endl;
//    ofBackground(ofMap(curVol, 0, soundSensitivity, 0, 1, false)*255);
    
}

void SoundReactivePlayer::updateFrame(){
    
    float curVol = this->getCurrentVolume();
    soFarMax = MAX(curVol, soFarMax);
    float max = soFarMax;
    float target_pct = ofMap(curVol, 0, max, 0, 1, true);
    
    target_pct *= getTotalNumFrames();
    
    currentFrame = target_pct;
    ++ frameCount;
    soFarMax *= 0.995;
}

bool SoundReactivePlayer::isMovieDone(){
    return frameCount > endFrameCount;
}
