  //
//  MovieManager.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/24.
//
//

#include "MovieManager.h"
#include "Util.hpp"
#include "Settings.h"
#include "NodeAnimator.hpp"

MovieManager::MovieManager(){
    
}

void MovieManager::setup(){
    
    if(true){//Settings::bMainScreen){
        sender.setup(Settings::sendHost, Settings::sendPort);
    }
    receiver.setup(Settings::receivePort);
    
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::movieData.size();
    
    currentPlayer = Util::getPlayerFrom(Settings::movieData[currentIndex]);
    nextPlayer = Util::getPlayerFrom(Settings::movieData[nextIndex]);
    
    currentPlayer->play();
    
    
    ofLog(OF_LOG_NOTICE) << "start `" << Settings::movieData[currentIndex]->getFilePath() << "`";
}

/**
    UPDATE TASK LIST
    1: Message Handling
        - check if there are message from osc,
        - if they are swap next Player
        - TODO:
 
    3: Check movie swap
        - if current movie has done, swap to next one...
 */
void MovieManager::update(){
    
    //1: Message Handling
    while (receiver.hasWaitingMessages()) {
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        string message = getMessageContentFromOfOSCMessage(msg);
        
        if (msg.getAddress() == "/birthday") {
            nextPlayer = Util::getPlayerFrom(Settings::birthdayData);
            nextPlayer->setMessage(message);
            nextPlayer->setMessagePosition(getCenterOf(nextPlayer));
            ofLog(OF_LOG_NOTICE) << "receive birthday message: fileName=" << Settings::birthdayData->getFilePath() << " name:" << message;
        }else if (msg.getAddress() == "/wedding") {
            nextPlayer = Util::getPlayerFrom(Settings::weddingData);
            nextPlayer->setMessage(message);
            nextPlayer->setMessagePosition(getCenterOf(nextPlayer));
            ofLog(OF_LOG_NOTICE) << "receive wedding message: fileName=" << Settings::weddingData->getFilePath() << " name:" << message;
        }else if (msg.getAddress() == "/message1") {
            
            this->textAnimationManager->setNext(TextDrawer::Alloc())
            ->setMessage(message)->setTiming(0,1500)
            ->setPosition(getCenterOf(nextPlayer))
            ->setAnimator(FastDrop::Alloc());
            
            ofLog(OF_LOG_NOTICE) << "receive new message:" << message;
            
        }else if (msg.getAddress() == "/message2") {
            
            this->textAnimationManager->setNext(TextDrawer::Alloc())
            ->setMessage(message)->setTiming(0,1500)
            ->setPosition(getCenterOf(nextPlayer))
            ->setAnimator(ScaleIn::Alloc());
            
            ofLog(OF_LOG_NOTICE) << "receive new message:" << message;
            
        }else if (msg.getAddress() == "/message3") {
            
            this->textAnimationManager->setNext(TextDrawer::Alloc())
            ->setMessage(message)->setTiming(0,1500)
            ->setPosition(getCenterOf(nextPlayer))
            ->setAnimator(SpinIn::Alloc());
            
            ofLog(OF_LOG_NOTICE) << "receive new message:" << message;
        }
    }
    
    
    //3: swap
    if(currentPlayer->isMovieDone()){
        switchMovie();
    }
    currentPlayer->updateFrame();
    
    this->textAnimationManager->update();
}

string MovieManager::getMessageContentFromOfOSCMessage(ofxOscMessage msg){
    string m = "";
    for(int i=0; i<msg.getNumArgs(); ++i){
        string buf = msg.getArgAsString(i);
        if(buf == "" || buf == " ")continue;
        if(i != 0 && i != msg.getNumArgs()) m += " ";
        m += buf;
    }
    return m;
}
ofPoint MovieManager::getCenterOf(shared_ptr<BaseVideoPlayer> p){
    return ofPoint(p->getWidth()/ 2, p->getHeight() / 2);
}

void MovieManager::draw(){
    ofSetColor(255);
    currentPlayer->drawMovie(0, 0, movieWidth, movieHeight);
    this->textAnimationManager->draw();
}






// private
/**
 * @param _file_names 読み込むファイル名
 */


/**
 * @param _nextMovieId 次のmovieのID
 */
void MovieManager::switchMovie(){
    
    currentPlayer = nextPlayer;
    nextPlayer = Util::getPlayerFrom(Settings::movieData[nextIndex()]);
    //ビデオは順番である必要はないから、ここで無条件でindex変えるのありだと思う
    currentIndex = nextIndex();
    
    // 動画を作成
    currentPlayer->firstFrame();
    ofLog(OF_LOG_NOTICE) << "switch to `" << currentPlayer->getMoviePath() << "`";
}

void MovieManager::setCurrendVolume(float _curVol){
    currentPlayer->setCurrentVolume(_curVol);
}

int MovieManager::nextIndex(){
    return (currentIndex + 1) % Settings::movieData.size();
}
