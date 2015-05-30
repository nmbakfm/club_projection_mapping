//
//  MovieManager.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/24.
//
//

#ifndef __clubProjectionMapping__MovieManager__
#define __clubProjectionMapping__MovieManager__

#define debugMode TRUE

#include "ofMain.h"
#include "Settings.h"

class MovieManager {
    vector<string> file_names;
    vector<int> file_order;
    
    ofVideoPlayer currentPlayer; // 今の映像
    ofVideoPlayer nextPlayer; // 次に流す映像
    ofVideoPlayer zimaPlayer; // zimaの映像
    
    int currentMovieId;
    int nextMovieId;
    
    int currentIndex;
    
    bool isZima;
    
    void switchMovie();
    
    void assignFileNames(vector<string> _file_names);
    void assignFileOrder(vector<int> _file_order);
public:
    MovieManager();
    void setup(vector<string> _file_names, vector<int> _file_order, string _zima_file_name);
    void update();
    void draw();
    void startZima();
    void setMoviePosition(double position_pct);
};

#endif /* defined(__clubProjectionMapping__MovieManager__) */
