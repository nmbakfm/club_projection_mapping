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
#include "ofxXmlSettings.h"

class Settings {
    static ofxXmlSettings xml;
    static ofPoint loadPoint(const string tagPath);
public:
    static void load(const string file_name);
    static ofPoint rect_vertices[4];
    static int mainFileNum;
    static vector<string> mainFileNames;
    static vector<int> mainFileOrder;
};

#endif /* defined(__clubProjectionMapping__Settings__) */
