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

void MovieManager::setup(vector<string> _file_names, vector<int> _file_order, string _zima_file_name){
    assignFileNames(_file_names);
    assignFileOrder(_file_order);
    fileCount = Settings::fileNames.size();
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::fileNames.size();
    
    currentMovieId = Settings::fileOrder[currentIndex];
    nextMovieId = Settings::fileOrder[nextIndex];
    
    currentPlayer.load(file_names[currentIndex]);
    nextPlayer.loadAsync(file_names[nextMovieId]);
    
    currentPlayer.play();
    currentPlayer.setUseTexture(true);
    
    zimaPlayer.load(_zima_file_name);
    isZima = false;
    zimaPlayer.setUseTexture(true);
}

void MovieManager::update(){
    if(isZima){
        zimaPlayer.update();
        if (zimaPlayer.getIsMovieDone()) {
            isZima = false;
            
            currentPlayer.play();
            currentPlayer.setFrame(0);
            currentPlayer.update();
        }
    }else{
        if(currentPlayer.getIsMovieDone()){
            switchMovie();
        }
        
        currentPlayer.update();
    }
}

void MovieManager::draw(){
    if (isZima) {
        if(zimaPlayer.isFrameNew()) zimaPlayer.draw(0, 0, 320, 240);
    }else{
        if (currentPlayer.isFrameNew()) currentPlayer.draw(0, 0, 320, 240);
    }
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
    
    
    ofLog(OF_LOG_NOTICE) << "switch to `" << file_names[currentMovieId] << "`(ZIMA MOVIE)";
}


// private
/**
 * @param _file_names 読み込むファイル名
 */
void MovieManager::assignFileNames(vector<string> _file_names){
    file_names = _file_names;
}

/**
 * @param _file_order ファイルを読み込む順番をIDの配列としたもの
 */
void MovieManager::assignFileOrder(vector<int> _file_order){
    file_order = _file_order;
}


/**
 * @param _nextMovieId 次のmovieのID
 */
void MovieManager::switchMovie(){
    currentIndex = (currentIndex + 1 < fileCount) ? currentIndex + 1 : 0;
    int nextIndex = (currentIndex + 1) % fileCount;
    currentMovieId = Settings::fileOrder[currentIndex];
    nextMovieId = Settings::fileOrder[nextIndex];
    
    currentPlayer = nextPlayer;
    nextPlayer.loadAsync(file_names[nextMovieId]);
    nextPlayer.setUseTexture(true);
    currentPlayer.setFrame(0);
    currentPlayer.play();
    
    ofLog(OF_LOG_NOTICE) << "switch to `" << file_names[currentMovieId] << "`";
}