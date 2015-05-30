//
//  Settings.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/04.
//
//

#include "Settings.h"

ofxXmlSettings Settings::xml;
ofPoint Settings::mainRectVertices[4];
vector<string> Settings::mainFileNames;
int Settings::mainFileNum;
vector<int> Settings::mainFileOrder;
string Settings::mainZimaFileName;

ofPoint Settings::subRectVertices[4];
vector<string> Settings::subFileNames;
int Settings::subFileNum;
vector<int> Settings::subFileOrder;
string Settings::subZimaFileName;

/**
 * @todo xmlからデータをロードする
 */
void Settings::load(const string file_name){
    xml.load(file_name);
    
    string dir_name = "480pi/";
    
    mainRectVertices[0] = ofPoint(100,150);
    mainRectVertices[1] = ofPoint(320,70);
    mainRectVertices[2] = ofPoint(480,500);
    mainRectVertices[3] = ofPoint(50,240);
    
    
    mainFileNum = 5;
    mainFileNames.push_back(dir_name+"6.mov");
    mainFileNames.push_back(dir_name+"1_fixed.mov");
    mainFileNames.push_back(dir_name+"zima_2.mov");
    mainFileOrder.push_back(0);
    mainFileOrder.push_back(1);
    mainFileOrder.push_back(2);
    mainFileOrder.push_back(1);
    mainFileOrder.push_back(0);
    
    mainZimaFileName = dir_name+"zima_2.mov";
    
    
    subRectVertices[0] = ofPoint(300,150);
    subRectVertices[1] = ofPoint(620,70);
    subRectVertices[2] = ofPoint(680,500);
    subRectVertices[3] = ofPoint(350,240);
    
    subFileNum = 5;
    subFileNames.push_back(dir_name+"1_fixed.mov");
    subFileNames.push_back(dir_name+"6.mov");
    subFileNames.push_back(dir_name+"zima_2.mov");
    subFileOrder.push_back(0);
    subFileOrder.push_back(1);
    subFileOrder.push_back(2);
    subFileOrder.push_back(1);
    
    subZimaFileName = dir_name+"zima_2.mov";
    
    
}

/**
 * 
 */
ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getValue(tagPath+":x", 0.0), xml.getValue(tagPath+":y", 0.0));
}