//
//  BirthdayVideoPlayer.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#ifndef __clubProjectionMapping__BirthdayVideoPlayer__
#define __clubProjectionMapping__BirthdayVideoPlayer__

#include "ofMain.h"
#include "BaseVideoPlayer.h"

class BirthdayVideoPlayer : public BaseVideoPlayer {
public:
    BirthdayVideoPlayer();
    
    void updateFrame();
    void drawMovie(float _x, float _y, float _w, float _h);
};

#endif /* defined(__clubProjectionMapping__BirthdayVideoPlayer__) */
