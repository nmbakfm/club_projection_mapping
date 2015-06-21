  //
//  MovieManager.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/24.
//
//

#include "MovieManager.h"

MovieManager::MovieManager(){
    
}

void MovieManager::setup(vector<string> _file_names, string _zima_file_name){
    assignFileNames(_file_names);
    
    if(Settings::bMainScreen){
        sender.setup(Settings::sendHost, Settings::sendPort);
    }
    receiver.setup(Settings::receivePort);
    movieType = MovieTypeNormal;
    
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::fileNames.size();
    
    currentPlayer = new ofVideoPlayer();
    nextPlayer = new ofVideoPlayer();
    currentPlayer->load(file_names[currentIndex]);
    nextPlayer->load(file_names[nextMovieId]);
    
    currentPlayer->play();
    currentPlayer->setUseTexture(true);
    
    zimaPlayer.load(_zima_file_name);
    movieType = MovieTypeNormal;
    zimaPlayer.setUseTexture(true);
    zimaAlpha = 0;
    zimaPlayer.setLoopState(OF_LOOP_NORMAL);
    
    if(!Settings::bMainScreen){
        zimaPlayer.setLoopState(OF_LOOP_NORMAL);
    }
    ofLog(OF_LOG_NOTICE) << "start `" << file_names[currentMovieId] << "`";
}

void MovieManager::update(){
    if(Settings::bMainScreen){
        while (receiver.hasWaitingMessages()) {
            ofxOscMessage msg;
            receiver.getNextMessage(&msg);
            if (msg.getAddress() == "/birthday") {
                nextPlayer = new ofVideoPlayer();
                nextPlayer->load(Settings::birthdayFileName);
                message = msg.getArgAsString(0);
                nextMovieType = MovieTypeBirthDay;
                ofLog(OF_LOG_NOTICE) << "receive birthday message: fileName=" << nextPlayer->getMoviePath() << " name:" << message;
            }
        }
    }else{
        while(receiver.hasWaitingMessages()){
            ofxOscMessage msg;
            receiver.getNextMessage(&msg);
            if (msg.getAddress() == "startZima") {
                if(msg.getArgAsInt32(0) == 0){
                    stopZima();
                }else{
                    startZima();
                }
            }
        }
    }
    
    if(movieType == MovieTypeZima){
        if(zimaAlpha < 255){
            zimaAlpha = MIN(zimaAlpha + 5, 255);
        }
        zimaPlayer.update();
        if(Settings::bMainScreen){
            if (zimaPlayer.getIsMovieDone()) {
                stopZima();
            }
        }
    }else{
        if (zimaAlpha > 0) {
            zimaAlpha = MAX(zimaAlpha - 5, 0);
        }
    }
    if(currentPlayer->getIsMovieDone()){
        switchMovie();
    }
    currentPlayer->update();
}

void MovieManager::draw(){
    ofSetColor(255);
    currentPlayer->draw(0, 0, movieWidth, movieHeight);
    ofSetColor(255, zimaAlpha);
    zimaPlayer.draw(0, 0, movieWidth, movieHeight);
}

/**
 *
 */
void MovieManager::startZima(){
    if(movieType == MovieTypeZima) return;
    movieType = MovieTypeZima;
    
    zimaPlayer.play();
    zimaPlayer.setFrame(0);
    zimaPlayer.update();
    
    if(Settings::bMainScreen){
        ofxOscMessage msg;
        msg.setAddress("startZima");
        msg.addIntArg(1);
        sender.sendMessage(msg);
    }
    
    ofLog(OF_LOG_NOTICE) << "start `" << zimaPlayer.getMoviePath() << "`(ZIMA MOVIE)";
}

void MovieManager::stopZima(){
    movieType = MovieTypeNormal;
    
    if(Settings::bMainScreen){
        ofxOscMessage msg;
        msg.setAddress("startZima");
        msg.addIntArg(0);
        sender.sendMessage(msg);
    }
    ofLog(OF_LOG_NOTICE) << "stop `" << zimaPlayer.getMoviePath() << "`(ZIMA MOVIE)";
}


// private
/**
 * @param _file_names 読み込むファイル名
 */
void MovieManager::assignFileNames(vector<string> _file_names){
    file_names = _file_names;
    fileCount = _file_names.size();
}

/**
 * @param _nextMovieId 次のmovieのID
 */
void MovieManager::switchMovie(){
    currentPlayer = nextPlayer;
    movieType = nextMovieType;
    nextPlayer = new ofVideoPlayer();
    nextPlayer->load(file_names[nextIndex()]);
    if(nextMovieType == MovieTypeNormal){
        // 現在の動画の次の順番へ
        currentIndex = nextIndex();
        
        // 動画の切り替え
        nextPlayer->setUseTexture(true);
    }else if(nextMovieType == MovieTypeBirthDay){
        ofLog(OF_LOG_NOTICE) << "START BIRTHDAY MOVIE...";
        nextPlayer->setUseTexture(true);
        nextMovieType = MovieTypeNormal;
    }
    
    if(currentIndex == 0){
        ofLog(OF_LOG_NOTICE) << "RETURN TO FIRST MOVIE...";
    }
    
    // 動画を作成
    currentPlayer->firstFrame();
    currentPlayer->play();
    ofLog(OF_LOG_NOTICE) << "switch to `" << currentPlayer->getMoviePath() << "`";
}

int MovieManager::nextIndex(){
    return (currentIndex + 1) % fileCount;
}

MovieManager::~MovieManager(){
    delete currentPlayer;
    delete nextPlayer;
}