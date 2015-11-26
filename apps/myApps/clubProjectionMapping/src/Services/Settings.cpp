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
float Settings::soundSensitivity;
float Settings::soFarMaxVol;
float Settings::movieWidth, Settings::movieHeight;
bool Settings::bMainScreen;
int Settings::sendPort;
string Settings::sendHost;
int Settings::receivePort;
int Settings::zimaInterval;
shared_ptr<MovieData> Settings::zimaData;
shared_ptr<MovieData> Settings::weddingData;
shared_ptr<MovieData> Settings::birthdayData;
vector<shared_ptr<MovieData> > Settings::movieData;

shared_ptr<ofTrueTypeFont> Settings::weddingFont;
shared_ptr<ofTrueTypeFont> Settings::birthdayFont;
shared_ptr<ofTrueTypeFont> Settings::normalFont;

void Settings::load(const string file_name){
    xml.load(file_name);
    
    xml.pushTag("settings");
    
    bMainScreen = (xml.getValue("mainScreenFlag", 1) != 0);
    
    string dir_name = xml.getValue("moviePath", "");
    soFarMaxVol = 0;
    
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
        ofLog(OF_LOG_FATAL_ERROR) << "動画ファイルが1つも読み込まれていません。`data/settings.xml`内を確認して下さい" << endl;
        throw "NoFileException";
    }
    
    ofLog(OF_LOG_NOTICE) << "MOVIE ORDERS =================================";
    for (int i=0; i<fileNum; ++i) {
        string filename = (dir_name + xml.getAttribute("movie","filename","",i));
        int endframe = (xml.getAttribute("movie","endFrame", 0, i));
        
        auto p = shared_ptr<MovieData>(new MovieData(filename, MovieTypeNormal));
        p->setEndFrameForSoundReactPlayer(endframe);
        
        movieData.push_back(p);
        
        if(!ofFile::doesFileExist(filename)){
            ofLog(OF_LOG_FATAL_ERROR) << "`" << filename << "` does not exists";
            throw "MovieFileNotFoundException";
        }else{
            ofLog(OF_LOG_NOTICE) << i << ":\t" << filename;
        }
    }
    xml.popTag(); // movies
    
    soundSensitivity = xml.getValue("soundSensitivity", 1.0);
    
    ofLog(OF_LOG_NOTICE) << "LOAD ZIMA =================================";
    xml.pushTag("zimaMovies");
    string zimaFileName = dir_name + xml.getAttribute("movie", "filename", "", 0);
    zimaData = shared_ptr<MovieData>(new MovieData(zimaFileName, MovieTypeZima));
    
    
    if(!ofFile::doesFileExist(zimaFileName)){
        ofLog(OF_LOG_FATAL_ERROR) << "`" << zimaFileName << "` does not exist";
        throw "MovieFileNotFoundException";
    }else{
        ofLog(OF_LOG_NOTICE) << zimaFileName;
    }
    xml.popTag(); // zimaMovies
    
    
    
    ofLog(OF_LOG_NOTICE) << "LOAD BIRTHDAY ==============================";
    xml.pushTag("birthdayMovies");
    string birthdayFileName = dir_name + xml.getAttribute("movie", "filename", "", 0);
    birthdayData = shared_ptr<MovieData>(new MovieData(birthdayFileName, MovieTypeBirthDay));
    
    if(!ofFile::doesFileExist(birthdayFileName)){
        ofLog(OF_LOG_FATAL_ERROR) << "`" << birthdayFileName << "` does not exist";
        throw "MovieFileNotFoundException";
    }else{
        ofLog(OF_LOG_NOTICE) << birthdayFileName;
    }
    xml.popTag(); // birthday
    
    ofLog(OF_LOG_NOTICE) << "LOAD WEDDING ==============================";
    xml.pushTag("weddingMovies");
    string weddingFileName = dir_name + xml.getAttribute("movie", "filename", "", 0);
    weddingData = shared_ptr<MovieData>(new MovieData(weddingFileName, MovieTypeWedding));
    
    if(!ofFile::doesFileExist(weddingFileName)){
        ofLog(OF_LOG_FATAL_ERROR) << "`" << weddingFileName << "` does not exist";
        throw "MovieFileNotFoundException";
    }else{
        ofLog(OF_LOG_NOTICE) << weddingFileName;
    }
    xml.popTag(); // wedding
    
    xml.popTag(); // settings
    
    movieWidth = xml.getAttribute("settings:movieSize", "width", 0.0);
    if(movieWidth <= 0){
        ofLog(OF_LOG_FATAL_ERROR) << "動画の幅指定が不正です。0より大きい値を指定してください";
        throw "MovieSizeInvalidException";
    }
    
    movieHeight = xml.getAttribute("settings:movieSize", "height", 0.0);
    if(movieHeight <= 0){
        ofLog(OF_LOG_FATAL_ERROR) << "動画の高さ指定が不正です。0より大きい値を指定してください";
        throw "MovieSizeInvalidException";
    }
    
    
    if (bMainScreen) {
        zimaInterval = xml.getValue("settings:zimaInterval", 0);
        sendHost = xml.getValue("settings:networking:send:host", "");
        sendPort = 57689;
        receivePort = 57688;
    }else{
        receivePort = 57689;
    }
    
    //font loading
    birthdayFont = shared_ptr<ofTrueTypeFont>(new ofTrueTypeFont());
    weddingFont = shared_ptr<ofTrueTypeFont>(new ofTrueTypeFont());
    normalFont = shared_ptr<ofTrueTypeFont>(new ofTrueTypeFont());
    birthdayFont->load("font/NuevaStd-Bold.otf", 72, true, true, true);
    normalFont->load("font/Impact.ttf", 72, true, true, true);
    weddingFont->load("font/lucida-bright.ttf", 72, true, true, true);
}

ofPoint Settings::loadPoint(const string tagPath){
    return ofPoint(xml.getAttribute(tagPath, "x", 0.0), xml.getAttribute(tagPath, "y", 0.0));
}