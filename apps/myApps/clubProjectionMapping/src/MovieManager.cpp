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
    
    movieWidth = Settings::movieWidth;
    movieHeight = Settings::movieHeight;
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::fileNames.size();
    
    currentMovieId = Settings::fileOrder[currentIndex];
    nextMovieId = Settings::fileOrder[nextIndex];
    
    currentPlayer.load(file_names[currentIndex]);
    nextPlayer.load(file_names[nextMovieId]);
    
    currentPlayer.play();
    currentPlayer.setUseTexture(true);
    
    zimaPlayer.load(_zima_file_name);
    isZima = false;
    zimaPlayer.setUseTexture(true);
    
    ofLog(OF_LOG_NOTICE) << "start `" << file_names[currentMovieId] << "`";
}

void MovieManager::update(){
    if(isZima){
        zimaPlayer.update();
        if (zimaPlayer.getIsMovieDone()) {
            isZima = false;
            
            currentPlayer.play();
            currentPlayer.firstFrame();
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
        if(zimaPlayer.isFrameNew()) zimaPlayer.draw(0, 0, movieWidth, movieHeight);
    }else{
        if (currentPlayer.isFrameNew()) currentPlayer.draw(0, 0, movieWidth, movieHeight);
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
    fileCount = _file_names.size();
}

/**
 * @param _file_order ファイルを読み込む順番をIDの配列としたもの
 */
void MovieManager::assignFileOrder(vector<int> _file_order){
    file_order = _file_order;
    orderCount = _file_order.size();
}


/**
 * @param _nextMovieId 次のmovieのID
 */
void MovieManager::switchMovie(){
    
    // 現在の動画の次の順番へ
    currentIndex = (currentIndex + 1) % orderCount;
    int nextIndex = (currentIndex + 1) % orderCount;
    
    // 現在と次の動画のIDを取得
    currentMovieId = Settings::fileOrder[currentIndex];
    nextMovieId = Settings::fileOrder[nextIndex];
    
    // 動画の切り替え
    currentPlayer = nextPlayer;
    nextPlayer.load(file_names[nextMovieId]);
    nextPlayer.setUseTexture(true);
    
    // 動画を作成
    currentPlayer.firstFrame();
    currentPlayer.play();
    
    ofLog(OF_LOG_NOTICE) << "switch to `" << file_names[currentMovieId] << "`";
}