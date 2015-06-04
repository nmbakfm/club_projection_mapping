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
vector<int> Settings::fileOrder;
string Settings::zimaFileName;


void Settings::load(const string file_name){
    xml.load(file_name);
    
    string rootPath = "settings";
    xml.pushTag("settings");
    
    string dir_name = xml.getValue("moviePath", "");
    
    
    // calibration
    xml.pushTag("calibration");
    
    xml.pushTag("rect");
    rectVertices[0] = loadPoint("leftTop");
    rectVertices[1] = loadPoint("rightTop");
    rectVertices[2] = loadPoint("rightBottom");
    rectVertices[3] = loadPoint("leftBottom");
    xml.popTag();
    
    xml.popTag(); //calibration
    
    xml.pushTag("movies");
    int fileNum = xml.getNumTags("movie");
    
    if (fileNum == 0) {
        ofLog(OF_LOG_WARNING) << "動画ファイルが1つも読み込まれていません。`data/settings.xml`内を確認して下さい" << endl;
    }
    
    for (int i=0; i<fileNum; ++i) {
        fileNames.push_back(dir_name + xml.getAttribute("movie","filename","",i));
    }
    xml.popTag(); // movies
    
    xml.pushTag("order");
    
    int orderNum = xml.getNumTags("movieId");
    if (orderNum == 0) {
        ofLog(OF_LOG_WARNING) << "動画ファイルの順番が確認できません。`data/settings.xml`内を確認して下さい" << endl;
    }
    
    ofLog(OF_LOG_NOTICE) << "MOVIE ORDERS =================================";
    for (int i=0; i<orderNum; ++i) {
        int movie_id = xml.getValue("movieId",0,i);
        fileOrder.push_back(movie_id);
        ofLog(OF_LOG_NOTICE) << i << ":\t" << movie_id << ":\t" << fileNames[movie_id];
    }
    xml.popTag();// order
    
    ofLog(OF_LOG_NOTICE) << "LOAD ZIMA =================================";
    xml.pushTag("zimaMovies");
    zimaFileName = dir_name + xml.getAttribute("movie", "filename", "", 0);
    ofLog(OF_LOG_NOTICE) << zimaFileName;
    xml.popTag();// zimaMovies

    xml.popTag(); // orderPath
    xml.popTag();//settings
}

/**
 * 
 */
ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getAttribute(tagPath, "x", 0.0), xml.getAttribute(tagPath, "y", 0.0));
}