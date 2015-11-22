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
#include <memory>
class MovieData;

class BaseVideoPlayer : public ofVideoPlayer {
    
private:
    string message = "";
    ofPoint pos = ofPoint(0,0);
    float curVol = 0;
    std::shared_ptr<MovieData> data;
    
protected:
    static ofTrueTypeFont weddingNameFont;
    static ofTrueTypeFont birthdayNameFont;
    
    
public:
    BaseVideoPlayer();
    virtual ofPoint getPosition(){};
    
    //MovieData set get
    shared_ptr<MovieData> getMovieData(){return data;};
    void setMovieData(shared_ptr<MovieData> _data){this->data = _data;}
    
    //Message getter,setter
    string getMessage(){return this->message;}
    void setMessage(string _message){this->message = message;}
    
    //Message position getter,setter
    ofPoint getMessagePosition(){return this->pos;}
    void setMessagePosition(float _x, float _y){this->pos = ofPoint(_x, _y);}
    void setMessagePosition(ofPoint _msg_pos){this->pos = pos;}
    
    //Volume getter, setter
    void setCurrentVolume(float _curVol){this->curVol = _curVol;}
    float getCurrentVolume(){return curVol;};
    
    void updateFrame(){update();}
    void drawMovie(float _x, float _y, float _w, float _h){draw(_x, _y, _w, _h);}
    bool isMovieDone(){return getIsMovieDone(); }
    
    static void setNameFont(string _font_name, int _font_size);
};

#endif /* defined(__clubProjectionMapping__BaseVideoPlayer__) */
