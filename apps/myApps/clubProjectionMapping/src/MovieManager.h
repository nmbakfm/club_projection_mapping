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
#include "Settings.h"
#include "Constant.h"
#include "ofxOsc.h"

typedef enum MovieType {
    MovieTypeNormal = 0,
    MovieTypeZima = 1,
    MovieTypeBirthDay = 2,
} ;

class MovieManager {
    vector<string> file_names;
    
    ofVideoPlayer currentPlayer; // 今の映像
    ofVideoPlayer nextPlayer; // 次に流す映像
    ofVideoPlayer zimaPlayer; // zimaの映像
    
    int fileCount;
    
    int currentMovieId;
    int nextMovieId;
    
    int currentIndex;
    
    string message;
    MovieType movieType;
    MovieType nextMovieType;
    
    bool isZima;
    
    void switchMovie();
    int nextIndex();
    
    void assignFileNames(vector<string> _file_names);
    
    float movieWidth, movieHeight;
    
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    int zimaAlpha;
    
public:
    MovieManager();
    void setup(vector<string> _file_names, string _zima_file_name);
    void update();
    void draw();
    void startZima();
    void stopZima();
    void setMoviePosition(double position_pct);
};

#endif /* defined(__clubProjectionMapping__MovieManager__) */
