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

void MovieManager::setup(vector<string> _file_names, vector<int> _endFrames, string _zima_file_name){
    assignFileNames(_file_names, _endFrames);
    
    BaseVideoPlayer::setNameFont("font/NuevaStd-Bold.otf", 72);
    
    if(Settings::bMainScreen){
        sender.setup(Settings::sendHost, Settings::sendPort);
    }
    receiver.setup(Settings::receivePort);
    movieType = MovieTypeNormal;
    
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::fileNames.size();
    
    if(endFrames[0] > 0) {
        currentPlayer = new SoundReactivePlayer(endFrames[0], Settings::soundSensitivity);
    }else{
        currentPlayer = new NormalVideoPlayer();
    }
    
    if(endFrames[nextIndex] > 0) {
        nextPlayer = new SoundReactivePlayer(endFrames[1], Settings::soundSensitivity);
    }else{
        nextPlayer = new NormalVideoPlayer();
    }
    
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
                BirthdayVideoPlayer *_birthdayVideoPlayer = new BirthdayVideoPlayer();
                _birthdayVideoPlayer->load(Settings::birthdayFileName);
                message = "";
                for(int i=0; i<msg.getNumArgs(); ++i){
                    if(i != 0) message += " ";
                    message += msg.getArgAsString(i);
                }
                _birthdayVideoPlayer->setMessage(message);
                _birthdayVideoPlayer->setNamePosition(_birthdayVideoPlayer->width/2, _birthdayVideoPlayer->height/2);
                delete nextPlayer;
                nextPlayer = _birthdayVideoPlayer;
                nextMovieType = MovieTypeBirthDay;
                ofLog(OF_LOG_NOTICE) << "receive birthday message: fileName=" << nextPlayer->getMoviePath() << " name:" << message;
            }else if (msg.getAddress() == "/wedding") {
                WeddingVideoPlayer *_weddingVideoPlayer = new WeddingVideoPlayer();
                _weddingVideoPlayer->load(Settings::weddingFileName);
                message = "";
                for(int i=0; i<msg.getNumArgs(); ++i){
                    if(i != 0) message += " ";
                    message += msg.getArgAsString(i);
                }
                _weddingVideoPlayer->setMessage(message);
                _weddingVideoPlayer->setNamePosition(_weddingVideoPlayer->width/2, _weddingVideoPlayer->height/2);
                delete nextPlayer;
                nextPlayer = _weddingVideoPlayer;
                nextMovieType = MovieTypeWedding;
                ofLog(OF_LOG_NOTICE) << "receive wedding message: fileName=" << nextPlayer->getMoviePath() << " name:" << message;
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
            if (zimaPlayer.isMovieDone()) {
                stopZima();
            }
        }
    }else{
        if (zimaAlpha > 0) {
            zimaAlpha = MAX(zimaAlpha - 5, 0);
        }
    }
    if(currentPlayer->isMovieDone()){
        switchMovie();
    }
    currentPlayer->updateFrame();
}

void MovieManager::draw(){
    ofSetColor(255);
    currentPlayer->drawMovie(0, 0, movieWidth, movieHeight);
    ofSetColor(255, zimaAlpha);
    zimaPlayer.drawMovie(0, 0, movieWidth, movieHeight);
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
void MovieManager::assignFileNames(vector<string> _file_names, vector<int> _endFrames){
    file_names = _file_names;
    fileCount = _file_names.size();
    endFrames = _endFrames;
}

/**
 * @param _nextMovieId 次のmovieのID
 */
void MovieManager::switchMovie(){
    delete currentPlayer;
    currentPlayer = nextPlayer;
    movieType = nextMovieType;
    if(endFrames[nextIndex()] > 0){
        nextPlayer = new SoundReactivePlayer(endFrames[nextIndex()], Settings::soundSensitivity);
    }else{
        nextPlayer = new NormalVideoPlayer();
    }
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
    }else if(nextMovieType == MovieTypeWedding){
        ofLog(OF_LOG_NOTICE) << "START WEDDING MOVIE...";
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

void MovieManager::setCurrendVolume(float _curVol){
//    curVol = _curVol;
    currentPlayer->setCurrentVolume(_curVol);
}

int MovieManager::nextIndex(){
    return (currentIndex + 1) % fileCount;
}
