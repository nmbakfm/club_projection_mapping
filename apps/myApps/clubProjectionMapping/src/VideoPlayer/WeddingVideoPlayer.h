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
    void setMessage(string _message);
    string getMessage();
    void setNamePosition(float _x, float _y);
    void setNamePosition(ofPoint _msg_pos);
    ofPoint getNamePosition();
    void update();
    void drawMovie(float _x, float _y, float _w, float _h);
    void getIsMovieDone();
};
#endif /* defined(__clubProjectionMapping__WeddingVideoPlayer__) */
