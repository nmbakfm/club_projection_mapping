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

void MovieManager::setup(vector<string> _file_names, vector<int> _file_order){
    assignFileNames(_file_names);
    assignFileOrder(_file_order);
    
    currentIndex = 0;
    int nextIndex = 1 % Settings::mainFileNum;
    currentMovieId = Settings::mainFileOrder[currentIndex];
    nextMovieId = Settings::mainFileOrder[nextIndex];
    currentPlayer.load(file_names[currentIndex]);
    nextPlayer.loadAsync(file_names[nextMovieId]);
    currentPlayer.play();
//    currentPlayer.setLoopState(OF_LOOP_NORMAL);
    currentPlayer.setUseTexture(true);
}

void MovieManager::update(){
//    cout << currentPlayer.isPlaying() << endl;
    if(currentPlayer.getIsMovieDone()){
        switchMovie();
    }
    
    currentPlayer.update();
    
}

void MovieManager::draw(){
    currentPlayer.draw(0, 0, 640, 480);
}

void MovieManager::setMoviePosition(double position_pct){
    currentPlayer.setPosition(position_pct);
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
    currentIndex = (currentIndex + 1 < Settings::mainFileNum) ? currentIndex + 1 : 0;
    int nextIndex = (currentIndex + 1) % Settings::mainFileNum;
    currentMovieId = Settings::mainFileOrder[currentIndex];
    nextMovieId = Settings::mainFileOrder[nextIndex];
    
    currentPlayer = nextPlayer;
    nextPlayer.loadAsync(file_names[nextMovieId]);
    nextPlayer.setUseTexture(true);
    currentPlayer.setPosition(0);
    currentPlayer.play();
}