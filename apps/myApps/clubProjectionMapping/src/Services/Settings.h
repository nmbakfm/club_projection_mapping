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
    static std::shared_ptr<MovieData> zimaData;
    static std::shared_ptr<MovieData> birthdayData;
    static std::shared_ptr<MovieData> weddingData;
    
    static std::shared_ptr<ofTrueTypeFont> weddingFont;
    static std::shared_ptr<ofTrueTypeFont> birthdayFont;
    static std::shared_ptr<ofTrueTypeFont> normalFont;
    
    static float soundSensitivity;
    
    static float movieWidth, movieHeight;
    static bool bMainScreen;
    
    static string sendHost;
    static int sendPort;
    
    static int receivePort;
    
    static int zimaInterval;
    
};

#endif /* defined(__clubProjectionMapping__Settings__) */
