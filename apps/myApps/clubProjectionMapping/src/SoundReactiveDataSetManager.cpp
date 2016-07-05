//
//  SoundReactiveDataSetManager.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2016/07/05.
//
//

#include "SoundReactiveDataSetManager.hpp"

map<string, TextureSequence> SoundRactiveDataManager::datas;
map<string, ofVideoPlayer> SoundRactiveDataManager::p_datas;


void SoundRactiveDataManager::addPath(string path){
    TextureSequence tq;
    datas.insert(DataSet::value_type(path, tq));
    ofVideoPlayer p;
    p.load(path);
    p_datas.insert(PlayerSet::value_type(path, p));
}

bool SoundRactiveDataManager::loadData(){
    for(auto&& d : datas){
        if(d.second.size() == 0){
            ofVideoPlayer p = p_datas.at(d.first);
            p.play();
            if(p.isPlaying() == false){
                return;
            }
            for(int i = 0; i < p.getTotalNumFrames(); i ++){
                p.setFrame(i);
                p.update();
                
                ofFbo fbo;
                fbo.allocate(p.getWidth(), p.getHeight());
                
                fbo.begin();
                ofClear(255);
                ofBackground(0);
                p.draw(0, 0, p.getWidth(), p.getHeight());
                fbo.end();
                d.second.push_back(fbo.getTexture());
            }
            p.stop();
            p.close();
        }else{
            //for this movie, load is done
        }
    }
    
    return true;
}

