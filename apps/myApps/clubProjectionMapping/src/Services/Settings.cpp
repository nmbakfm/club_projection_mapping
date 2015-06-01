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
    
    string rootPath = "settings";
    
    string dir_name = xml.getValue(rootPath + ":moviePath", "");
    
    // main
    string mainPath = rootPath + ":main";
    
    string mainCalibrationPath = mainPath + ":calibration:rect";
    mainRectVertices[0] = loadPoint(mainCalibrationPath + ":leftTop");
    mainRectVertices[1] = loadPoint(mainCalibrationPath + ":rightTop");
    mainRectVertices[2] = loadPoint(mainCalibrationPath + ":rightBottom");
    mainRectVertices[3] = loadPoint(mainCalibrationPath + ":leftBottom");
    
    string mainMoviesPath = mainPath + ":movies";
    mainFileNum = xml.getAttribute(mainMoviesPath, "count", 0);
    for (int i=0; i<mainFileNum; ++i) {
        mainFileNames.push_back(dir_name + xml.getAttribute(mainMoviesPath + ":movie", "filename", "", i));
    }
    
    string mainOrderPath = mainPath + ":order";
    int mainOrderNum = xml.getAttribute(mainOrderPath, "count", 0);
    for (int i=0; i<mainOrderNum; ++i) {
        mainFileOrder.push_back(xml.getValue(mainOrderPath + "movieId", 0, i));
    }
    
    string mainZimaPath = mainPath + ":zimaMovies";
    mainZimaFileName = dir_name + xml.getAttribute(mainZimaPath + ":movie", "filename", "", 0);
    
    
    
    // sub
    string subPath = rootPath + ":sub";
    
    string subCalibrationPath = subPath + ":calibration:rect";
    subRectVertices[0] = loadPoint(subCalibrationPath + ":leftTop");
    subRectVertices[1] = loadPoint(subCalibrationPath + ":rightTop");
    subRectVertices[2] = loadPoint(subCalibrationPath + ":rightBottom");
    subRectVertices[3] = loadPoint(subCalibrationPath + ":leftBottom");
    
    string subMoviesPath = subPath + ":movies";
    subFileNum = xml.getAttribute(subMoviesPath, "count", 0);
    for (int i=0; i<subFileNum; ++i) {
        subFileNames.push_back(dir_name + xml.getAttribute(subMoviesPath + ":movie", "filename", "", i));
    }
    
    string subOrderPath = subPath + ":order";
    int subOrderNum = xml.getAttribute(subOrderPath, "count", 0);
    for (int i=0; i<subOrderNum; ++i) {
        subFileOrder.push_back(xml.getValue(subOrderPath + "movieId", 0, i));
    }
    
    string subZimaPath = subPath + ":zimaMovies";
    subZimaFileName = dir_name + xml.getAttribute(subZimaPath + ":movie", "filename", "", 0);
    
}

/**
 * 
 */
ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getAttribute(tagPath, "x", 0.0), xml.getAttribute(tagPath, "y", 0.0));
}