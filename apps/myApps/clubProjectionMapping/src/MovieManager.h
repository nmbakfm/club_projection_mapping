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
#include "Constant.h"
#include "ClubVideoPlayer.h"
#include "Data.hpp"
#include "TextAnimationManager.hpp"


class MovieManager {
    
    shared_ptr<BaseVideoPlayer>  currentPlayer; // 今の映像
    shared_ptr<BaseVideoPlayer>  nextPlayer; // 次に流す映像
    vector<shared_ptr<MovieData> > adDataSequence; // 広告の順番
    shared_ptr<TextAnimationManager> textAnimationManager = TextAnimationManager::getInstance();
    
    int currentIndex;
    
    int currentAdIndex;
    int currentFrameSum;
    
    void switchMovie();
    int nextIndex();
    
    float movieWidth, movieHeight;
    float curVol;
    
    ofxOscReceiver receiver;
    
    
private:
    string getMessageContentFromOfOSCMessage(ofxOscMessage msg);
    ofPoint getCenterOf(shared_ptr<BaseVideoPlayer> p);
    bool isAdTiming();
    shared_ptr<MovieData> getNextAd();
    
    
public:
    MovieManager();
    void setup();
    void update();
    void draw();
    void setMoviePosition(double position_pct);
    void setCurrendVolume(float _curVol);
};

#endif /* defined(__clubProjectionMapping__MovieManager__) */
