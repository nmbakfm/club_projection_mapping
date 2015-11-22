//
//  WeddingVideoPlayer.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/07/09.
//
//

#ifndef __clubProjectionMapping__WeddingVideoPlayer__
#define __clubProjectionMapping__WeddingVideoPlayer__

#include "ofMain.h"
#include "BaseVideoPlayer.h"

class WeddingVideoPlayer : public BaseVideoPlayer {
public:
    WeddingVideoPlayer();
    
    void updateFrame();
    void drawMovie(float _x, float _y, float _w, float _h);
    bool getIsMovieDone();
};
#endif /* defined(__clubProjectionMapping__WeddingVideoPlayer__) */
