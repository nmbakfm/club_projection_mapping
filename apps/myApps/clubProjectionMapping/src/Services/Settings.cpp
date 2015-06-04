//
//  Settings.cpp
//  clubProjectionMapping
//
//  Created by 南部 晃史 on 2015/05/04.
//
//

#include "Settings.h"

ofxXmlSettings Settings::xml;
ofPoint Settings::rectVertices[4];
vector<string> Settings::fileNames;
int Settings::fileNum;
vector<int> Settings::fileOrder;
string Settings::zimaFileName;


void Settings::load(const string file_name){
    xml.load(file_name);
    
    string rootPath = "settings";
    
    string dir_name = xml.getValue(rootPath + ":moviePath", "");
    
    string calibrationPath = rootPath + ":calibration:rect";
    rectVertices[0] = loadPoint(calibrationPath + ":leftTop");
    rectVertices[1] = loadPoint(calibrationPath + ":rightTop");
    rectVertices[2] = loadPoint(calibrationPath + ":rightBottom");
    rectVertices[3] = loadPoint(calibrationPath + ":leftBottom");
    
    string moviesPath = rootPath + ":movies";
    fileNum = xml.getAttribute(moviesPath, "count", 1);
    if (fileNum) {
        ofLog(OF_LOG_WARNING) << "動画ファイルが1つも読み込まれていません。`data/settings.xml`内を確認して下さい" << endl;
    }
    
    for (int i=0; i<fileNum; ++i) {
        fileNames.push_back(dir_name + xml.getAttribute(moviesPath + ":movie", "filename", "", i));
    }
    
    string orderPath = rootPath + ":order";
    int orderNum = xml.getAttribute(orderPath, "count", 0);
    for (int i=0; i<orderNum; ++i) {
        fileOrder.push_back(xml.getValue(orderPath + "movieId", 0, i));
    }
    
    string mainZimaPath = rootPath + ":zimaMovies";
    zimaFileName = dir_name + xml.getAttribute(mainZimaPath + ":movie", "filename", "", 0);
    
}

/**
 * 
 */
ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getAttribute(tagPath, "x", 0.0), xml.getAttribute(tagPath, "y", 0.0));
}