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
vector<string> Settings::mainFileNames;
int Settings::mainFileNum;
vector<int> Settings::mainFileOrder;

/**
 * @todo xmlからデータをロードする
 */
void Settings::load(const string file_name){
    xml.load(file_name);
    
//    rect_vertices[0] = loadPoint("settings:calibration:rect:leftTop");
//    rect_vertices[1] = loadPoint("settings:calibration:rect:rightTop");
//    rect_vertices[2] = loadPoint("settings:calibration:rect:rightBottom");
//    rect_vertices[3] = loadPoint("settings:calibration:rect:leftBottom");
    rect_vertices[0] = ofPoint(0,0);
    rect_vertices[1] = ofPoint(640,0);
    rect_vertices[2] = ofPoint(640,480);
    rect_vertices[3] = ofPoint(0,480);
    
    mainFileNum = 5;
    mainFileNames.push_back("6.mov");
    mainFileNames.push_back("1_fixed.mov");
    mainFileNames.push_back("zima_2.mov");
    mainFileOrder.push_back(0);
    mainFileOrder.push_back(1);
    mainFileOrder.push_back(2);
    mainFileOrder.push_back(1);
    mainFileOrder.push_back(0);
}

/**
 * 
 */
ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getValue(tagPath+":x", 0.0), xml.getValue(tagPath+":y", 0.0));
}