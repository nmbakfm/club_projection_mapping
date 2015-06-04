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

class Settings {
    static ofxXmlSettings xml;
    static ofPoint loadPoint(const string tagPath);
public:
    static void load(const string file_name);
    static ofPoint rectVertices[4];
    static vector<string> fileNames;
    static vector<int> fileOrder;
    static string zimaFileName;
    
    static float movieWidth, movieHeight;
    static bool bMainScreen;
    
    static string sendHost;
    static string sendPort;
    
    static string receivePort;
};

#endif /* defined(__clubProjectionMapping__Settings__) */
