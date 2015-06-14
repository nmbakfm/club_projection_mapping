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
string Settings::zimaFileName;
float Settings::movieWidth, Settings::movieHeight;
bool Settings::bMainScreen;
int Settings::sendPort;
string Settings::sendHost;
int Settings::receivePort;
int Settings::zimaInterval;

void Settings::load(const string file_name){
    xml.load(file_name);
    
    xml.pushTag("settings");
    
    bMainScreen = (xml.getValue("mainScreenFlag", 1) != 0);
    
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
    
    ofLog(OF_LOG_NOTICE) << "MOVIE ORDERS =================================";
    for (int i=0; i<fileNum; ++i) {
        fileNames.push_back(dir_name + xml.getAttribute("movie","filename","",i));
        if(!ofFile::doesFileExist(fileNames[i])){
            ofLog(OF_LOG_WARNING) << "`" << fileNames[i] << "` does not exists";
            throw "MovieFileNotFoundException";
        }else{
            ofLog(OF_LOG_NOTICE) << i << ":\t" << fileNames[i];
        }
    }
    xml.popTag(); // movies
    
    ofLog(OF_LOG_NOTICE) << "LOAD ZIMA =================================";
    xml.pushTag("zimaMovies");
    zimaFileName = dir_name + xml.getAttribute("movie", "filename", "", 0);
    if(!ofFile::doesFileExist(zimaFileName)){
        ofLog(OF_LOG_WARNING) << "`" << zimaFileName << "` does not exist";
        throw "MovieFileNotFoundException";
    }else{
        ofLog(OF_LOG_NOTICE) << zimaFileName;
    }
    xml.popTag(); // zimaMovies
    xml.popTag(); // orderPath
    xml.popTag(); // settings
    
    
    movieWidth = xml.getAttribute("settings:movieSize", "width", 0.0);
    movieHeight = xml.getAttribute("settings:movieSize", "height", 0.0);
    
    if (bMainScreen) {
        zimaInterval = xml.getValue("settings:zimaInterval", 0);
        sendHost = xml.getValue("settings:networking:send:host", "");
        sendPort = 57689;
    }else{
        receivePort = 57689;
    }
}

ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getAttribute(tagPath, "x", 0.0), xml.getAttribute(tagPath, "y", 0.0));
}