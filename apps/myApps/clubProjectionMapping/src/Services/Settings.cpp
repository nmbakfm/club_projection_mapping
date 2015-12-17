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
int Settings::sendPort;
int Settings::FPS = 30;
string Settings::sendHost;
int Settings::receivePort;
shared_ptr<MovieData> Settings::weddingData;
shared_ptr<MovieData> Settings::birthdayData;
vector<shared_ptr<MovieData> > Settings::movieData;
vector<shared_ptr<MovieData> > Settings::adMovieData;

shared_ptr<ofTrueTypeFont> Settings::weddingFont;
shared_ptr<ofTrueTypeFont> Settings::birthdayFont;
shared_ptr<ofTrueTypeFont> Settings::normalFont;

void Settings::load(const string file_name){
    xml.load(file_name);
    
    xml.pushTag("settings");
    
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
    
    ofLog(OF_LOG_NOTICE) << "LOAD MOVIES =================================";
    for (int i=0; i<fileNum; ++i) {
        
        
        //check if there are movie
        string filepath= (dir_name + xml.getAttribute("movie","filename","",i));
        if(!ofFile::doesFileExist(filepath)){
            ofLog(OF_LOG_FATAL_ERROR) << "`" << filepath << "` does not exists";
            throw "MovieFileNotFoundException";
        }else{
            ofLog(OF_LOG_NOTICE) << i << ":\t" << filepath;
        }
        
        //put movie according to type
        int testSR = (xml.getAttribute("movie","endFrame", 0, i));
        string type = (xml.getAttribute("movie","type","normal",i));
        if(type == "normal"){
            auto p = shared_ptr<MovieData>(new MovieData(filepath, MovieTypeNormal));
            movieData.push_back(p);
            
        }else if(type == "soundReactive" || testSR != 0){
            auto p = shared_ptr<MovieData>(new MovieData(filepath, MovieTypeSoundReactive));
            int endframe = (xml.getAttribute("movie","endFrame", 0, i));
            p->setEndFrameForSoundReactPlayer(endframe);
            movieData.push_back(p);
            
        }else if(type == "advertise"){
            auto p = shared_ptr<MovieData>(new MovieData(filepath, MovieTypeAd));
            float timesParHouer = (xml.getAttribute("movie","timesParHouer", 1, i));
            p->setAdTimesParHoure(timesParHouer);
            adMovieData.push_back(p);
            
        }else if(type == "birthday"){
            birthdayData = shared_ptr<MovieData>(new MovieData(filepath, MovieTypeBirthDay));
            
        }else if(type == "wedding"){
            weddingData = shared_ptr<MovieData>(new MovieData(filepath, MovieTypeWedding));
        }
        
    }
    xml.popTag(); // movies
    soundSensitivity = xml.getValue("soundSensitivity", 1.0);
    
    movieWidth = xml.getAttribute("movieSize", "width", 0.0);
    if(movieWidth <= 0){
        ofLog(OF_LOG_FATAL_ERROR) << "動画の幅指定が不正です。0より大きい値を指定してください";
        throw "MovieSizeInvalidException";
    }
    
    movieHeight = xml.getAttribute("movieSize", "height", 0.0);
    if(movieHeight <= 0){
        ofLog(OF_LOG_FATAL_ERROR) << "動画の高さ指定が不正です。0より大きい値を指定してください";
        throw "MovieSizeInvalidException";
    }
    
    
    sendHost = xml.getValue("networking:send:host", "");
    sendPort = 57689;
    receivePort = 57688;
    
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