//
//  SoundReactiveVideoPlayer.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/07/16.
//
//

#include "SoundReactiveVideoPlayer.h"

#define FRAME_SMOOTHING_VAL 0.95

SoundReactivePlayer::SoundReactivePlayer(){
    frameCount = 0;
}

SoundReactivePlayer::SoundReactivePlayer(int _endFrameCount){
    frameCount = 0;
    endFrameCount = _endFrameCount;
}

void SoundReactivePlayer::drawMovie(float _x, float _y, float _w, float _h){
    draw(_x, _y, _w, _h);
//    ofBackground(curVol*255);
}

void SoundReactivePlayer::update(){
//    ofVideoPlayer::stop();
    int currentFrame = (int)(currentFrame * FRAME_SMOOTHING_VAL + getTotalNumFrames() * curVol * (1 - FRAME_SMOOTHING_VAL));
    currentFrame = ofMap(currentFrame, 1, getTotalNumFrames(), 1, getTotalNumFrames());
    cout << currentFrame << endl;
//    cout << "total:\t\t\t" << getTotalNumFrames() << endl;
//    cout << "currentFrame:\t" << currentFrame << endl;
//    cout << "curVol:\t" << curVol << endl;
    setFrame(currentFrame);
//    setFrame(frameCount);
//    setFrame();
    ofVideoPlayer::update();
    ++ frameCount;
}

bool SoundReactivePlayer::isMovieDone(){
    return frameCount > endFrameCount;
}