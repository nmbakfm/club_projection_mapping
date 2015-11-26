//
//  BaseVideoPlayer.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/06/21.
//
//

#ifndef __clubProjectionMapping__BaseVideoPlayer__
#define __clubProjectionMapping__BaseVideoPlayer__

#include <memory>
#include "ofMain.h"
#include "Settings.h"

class MovieData;

class BaseVideoPlayer : public ofVideoPlayer {
    
private:
    string message = "";
    ofPoint pos = ofPoint(0,0);
    float curVol = 0;
    std::shared_ptr<MovieData> data;
    bool _messageSensitive = false;
    
protected:
    
    
public:
    BaseVideoPlayer();
    
    //MovieData set get
    shared_ptr<MovieData> getMovieData(){return data;};
    void setMovieData(shared_ptr<MovieData> _data){this->data = _data;}
    
   
    //Message getter,setter
    //旧ビデオプレイヤーがMessageと結合していた名残
    //Wedding等ビデオプレーヤーと密接な関係を持つものに対して現在も有効
    //MessageDrawerを利用させるようにリファクタリングの対象
    virtual string getMessage(){return this->message;}
    virtual void setMessage(string _message){this->message = _message;}
    bool hasMessage(){return this->message != "";}
    
    //Message position getter,setter
    virtual ofPoint getMessagePosition(){return this->pos;}
    virtual void setMessagePosition(float _x, float _y){this->pos = ofPoint(_x, _y);}
    virtual void setMessagePosition(ofPoint _msg_pos){this->pos = _msg_pos;}
    
    //Volume getter, setter
    virtual void setCurrentVolume(float _curVol){this->curVol = _curVol;}
    virtual float getCurrentVolume(){return curVol;};
    
    virtual void updateFrame(){update();}
    virtual void drawMovie(float _x, float _y, float _w, float _h) = 0;
    virtual bool isMovieDone(){return getIsMovieDone(); }
    
    ~BaseVideoPlayer(){ ofLogNotice("=========movie " + this->getMovieData()->getFilePath() +  " deallcated========="); }
    
};

#endif /* defined(__clubProjectionMapping__BaseVideoPlayer__) */
