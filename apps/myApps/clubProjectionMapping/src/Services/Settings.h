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
public:
    static void load(const string file_name);
    static ofPoint loadPoint(const string tagPath);
    static ofPoint rect_vertices[4];
};

#endif /* defined(__clubProjectionMapping__Settings__) */
