//
//  Util.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#include "Util.hpp"
using namespace std;

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
        case MovieTypeZima:{
            p = shared_ptr<BaseVideoPlayer>(new NormalVideoPlayer());
            break;
        }
    }
    p->load(d->getFilePath());
    p->setMovieData(d);
    p->setUseTexture(true);
    
    return p;
}