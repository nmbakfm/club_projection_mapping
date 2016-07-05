//
//  SoundReactiveVideoPlayer.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/07/16.
//
//

#ifndef __clubProjectionMapping__SoundReactiveVideoPlayer__
#define __clubProjectionMapping__SoundReactiveVideoPlayer__

#include "ofMain.h"
#include "BaseVideoPlayer.h"

class SoundReactivePlayer : public BaseVideoPlayer {
    int frameCount;
    float soundSensitivity;
    int currentFrame;
    int endFrameCount;
    static float soFarMax;
public:
    SoundReactivePlayer();
    SoundReactivePlayer(int _endFrameCount, float _soundSensitivity);
    void updateFrame();
    void drawMovie(float _x, float _y, float _w, float _h);
    bool isMovieDone();
};

#endif /* defined(__clubProjectionMapping__SoundReactiveVideoPlayer__) */
