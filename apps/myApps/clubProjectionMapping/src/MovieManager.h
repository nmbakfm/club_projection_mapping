//
//  MovieManager.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/24.
//
//

#ifndef __clubProjectionMapping__MovieManager__
#define __clubProjectionMapping__MovieManager__

#include "ofMain.h"
#include "ofxOsc.h"
#include "Settings.h"
#include "Constant.h"
#include "ClubVideoPlayer.h"
#include "Data.hpp"


class MovieManager {
    
    shared_ptr<BaseVideoPlayer>  currentPlayer; // 今の映像
    shared_ptr<BaseVideoPlayer>  nextPlayer; // 次に流す映像
    shared_ptr<BaseVideoPlayer> zimaPlayer; // zimaの映像
    
    int currentIndex;
    shared_ptr<MovieData> currentData;
    
    string message;
    
    void switchMovie();
    int nextIndex();
    
    float movieWidth, movieHeight;
    float curVol;
    
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    int zimaAlpha;
    
private:
    string getMessageContentFromOfOSCMessage(ofxOscMessage msg);
    
public:
    MovieManager();
    void setup();
    void update();
    void draw();
    void startZima();
    void stopZima();
    void reserveZima();
    void setMoviePosition(double position_pct);
    void setCurrendVolume(float _curVol);
};

#endif /* defined(__clubProjectionMapping__MovieManager__) */
