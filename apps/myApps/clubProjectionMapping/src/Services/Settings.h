//
//  Settings.h
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/04.
//
//

#ifndef __clubProjectionMapping__Settings__
#define __clubProjectionMapping__Settings__

#include "ofMain.h"
#include "Constant.h"
#include "ofxXmlSettings.h"
#include "Data.hpp"
#include "CountDownManager.hpp"

class MovieData;



class MovieInfo{
    string fileName;
};

class Settings {
    static ofxXmlSettings xml;
    static ofPoint loadPoint(const string tagPath);
public:
    static void load(const string file_name);
    
    static ofPoint rectVertices[4];
    static vector<shared_ptr<MovieData> > movieData;
    static vector<shared_ptr<MovieData> > adMovieData;
    static std::shared_ptr<MovieData> birthdayData;
    static std::shared_ptr<MovieData> weddingData;
    
    static std::shared_ptr<ofTrueTypeFont> weddingFont;
    static std::shared_ptr<ofTrueTypeFont> birthdayFont;
    static std::shared_ptr<ofTrueTypeFont> normalFont;
    
    static CountDownManager<MovieData> movieCountDownManager;
    static CountDownManager<string> textCountManager;
    
    static float soundSensitivity;
    static float soFarMaxVol;
    static int FPS;
    
    static float movieWidth, movieHeight;
    
    static string sendHost;
    static int sendPort;
    
    static int receivePort;
    
    
};

#endif /* defined(__clubProjectionMapping__Settings__) */
