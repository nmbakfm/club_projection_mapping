//
//  NormalVideoPlayer.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#ifndef __clubProjectionMapping__NormalVideoPlayer__
#define __clubProjectionMapping__NormalVideoPlayer__

#include "ofMain.h"
#include "BaseVideoPlayer.h"

class NormalVideoPlayer : public BaseVideoPlayer {
public:
    NormalVideoPlayer(){};
    void setMessage(string _message){};
    string getMessage(){};
    void setPosition(float _x, float _y){};
    void setPosition(ofPoint _msg_pos){};
    ofPoint getPosition(){};
    void drawMovie(float _x, float _y, float _w, float _h){
        draw(_x, _y, _w, _h);
    };
};

#endif /* defined(__clubProjectionMapping__NormalVideoPlayer__) */
