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
    }else{
        receiver.setup(Settings::receivePort);
    }
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::fileNames.size();
    
    currentPlayer.load(file_names[currentIndex]);
    nextPlayer.load(file_names[nextMovieId]);
    
    currentPlayer.play();
    currentPlayer.setUseTexture(true);
    
    zimaPlayer.load(_zima_file_name);
    isZima = false;
    zimaPlayer.setUseTexture(true);
    zimaAlpha = 0;
    zimaPlayer.setLoopState(OF_LOOP_NORMAL);
    
    if(!Settings::bMainScreen){
        zimaPlayer.setLoopState(OF_LOOP_NORMAL);
    }
    ofLog(OF_LOG_NOTICE) << "start `" << file_names[currentMovieId] << "`";
}

void MovieManager::update(){
    if(!Settings::bMainScreen){
        while(receiver.hasWaitingMessages()){
            ofxOscMessage msg;
            receiver.getNextMessage(&msg);
           int test = msg.getNumArgs();
            if (msg.getAddress() == "startZima") {
                if(msg.getArgAsInt32(0) == 0){
                    stopZima();
                }else{
                    startZima();
                }
            }
        }
    }
    
    if(isZima){
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
    if(currentPlayer.getIsMovieDone()){
        switchMovie();
    }
    currentPlayer.update();
}

void MovieManager::draw(){
    ofSetColor(255);
    currentPlayer.draw(0, 0, movieWidth, movieHeight);
    ofSetColor(255, zimaAlpha);
    zimaPlayer.draw(0, 0, movieWidth, movieHeight);
}

void MovieManager::setMoviePosition(double position_pct){
    currentPlayer.setPosition(position_pct);
}

/**
 *
 */
void MovieManager::startZima(){
    if(isZima) return;
    isZima = true;
    
    zimaPlayer.play();
    zimaPlayer.setFrame(0);
    zimaPlayer.update();
    
    if(Settings::bMainScreen){
        ofxOscMessage msg;
        msg.setAddress("startZima");
        msg.addIntArg(1);
        sender.sendMessage(msg);
    }
    
    ofLog(OF_LOG_NOTICE) << "start `" << Settings::zimaFileName << "`(ZIMA MOVIE)";
}

void MovieManager::stopZima(){
    isZima = false;
    
    if(Settings::bMainScreen){
        ofxOscMessage msg;
        msg.setAddress("startZima");
        msg.addIntArg(0);
        sender.sendMessage(msg);
    }
    ofLog(OF_LOG_NOTICE) << "stop `" << Settings::zimaFileName << "`(ZIMA MOVIE)";
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
    // 現在の動画の次の順番へ
    currentIndex = nextIndex();
    if(currentIndex == 0){
        ofLog(OF_LOG_NOTICE) << "RETURN TO FIRST MOVIE...";
    }
    // 動画の切り替え
    currentPlayer = nextPlayer;
    nextPlayer.load(file_names[nextIndex()]);
    nextPlayer.setUseTexture(true);
    
    // 動画を作成
    currentPlayer.firstFrame();
    currentPlayer.play();
    
    ofLog(OF_LOG_NOTICE) << "switch to `" << Settings::fileNames[currentIndex] << "`";
}

int MovieManager::nextIndex(){
    return (currentIndex + 1) % fileCount;
}
