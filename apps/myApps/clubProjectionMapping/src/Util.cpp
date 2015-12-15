//
//  Util.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#include "Util.hpp"
#include <ctime>
using namespace std;

string Util::printDate(){
  
    // current date/time based on current system
    time_t now = time(0);
    
    // convert now to string form
    char* dt = ctime(&now);
    
    stringstream ss;
    ss << "The local date and time is: " << dt ;
    
    return ss.str();
}

shared_ptr<BaseVideoPlayer> Util::getPlayerFrom(shared_ptr<MovieData> d){
    
    shared_ptr<BaseVideoPlayer> p;
    
    switch (d->getMovieType()) {
        case MovieTypeNormal:{
            p = shared_ptr<BaseVideoPlayer>(new NormalVideoPlayer());
            break;
        }
        case MovieTypeSoundReactive:{
            p = shared_ptr<BaseVideoPlayer>(new SoundReactivePlayer(d->getEndFrame(), Settings::soundSensitivity));
            break;
        }
        case MovieTypeWedding:{
            p = shared_ptr<BaseVideoPlayer>(new WeddingVideoPlayer());
            break;
        }
        case MovieTypeBirthDay:{
            p = shared_ptr<BaseVideoPlayer>(new BirthdayVideoPlayer());
            break;
        }
        case MovieTypeAd:{
            p = shared_ptr<BaseVideoPlayer>(new NormalVideoPlayer());
            break;
        }
    }
    p->load(d->getFilePath());
    p->setMovieData(d);
    p->setUseTexture(true);
    
    return p;
}