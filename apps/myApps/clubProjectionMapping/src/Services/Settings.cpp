//
//  Settings.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/04.
//
//

#include "Settings.h"

ofxXmlSettings Settings::xml;
ofPoint Settings::rect_vertices[4];

void Settings::load(const string file_name){
    xml.load(file_name);
    
    rect_vertices[0] = loadPoint("settings:calibration:rect:leftTop");
    rect_vertices[1] = loadPoint("settings:calibration:rect:rightTop");
    rect_vertices[2] = loadPoint("settings:calibration:rect:rightBottom");
    rect_vertices[3] = loadPoint("settings:calibration:rect:leftBottom");
}

ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getValue(tagPath+":x", 0), xml.getValue(tagPath+":y", 0));
}