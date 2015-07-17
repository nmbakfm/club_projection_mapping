//
//  BaseVideoPlayer.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#ifndef __clubProjectionMapping__BaseVideoPlayer__
#define __clubProjectionMapping__BaseVideoPlayer__

#include "ofMain.h"

class BaseVideoPlayer : public ofVideoPlayer {
protected:
    string message;
    ofPoint pos;
    static ofTrueTypeFont nameFont;
    static string font_name;
    static int font_size;
    int endFrameCount;
    float curVol;
public:
    BaseVideoPlayer();
    virtual void setMessage(string _message){};
    virtual string getMessage(){};
    virtual void setPosition(float _x, float _y){};
    virtual void setPosition(ofPoint _msg_pos){};
    virtual ofPoint getPosition(){};
    virtual void drawMovie(float _x, float _y, float _w, float _h){ofVideoPlayer::draw(_x, _y, _w, _h);};
    virtual bool isMovieDone(){return getIsMovieDone(); };
    void setCurrentVolume(float _curVol);
    
    static void setNameFont(string _font_name, int _font_size);

    void update();
    void draw(float _x, float _y, float _w, float _h);
};

#endif /* defined(__clubProjectionMapping__BaseVideoPlayer__) */
