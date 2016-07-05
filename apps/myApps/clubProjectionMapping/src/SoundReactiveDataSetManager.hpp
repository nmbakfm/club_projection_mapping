//
//  SoundReactiveDataSetManager.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2016/07/05.
//
//

#ifndef SoundReactiveDataSetManager_hpp
#define SoundReactiveDataSetManager_hpp

#include <stdio.h>
#include <ofMain.h>

typedef vector<ofTexture> TextureSequence;
class SoundRactiveDataManager{
    
    
public:
    typedef map<string, TextureSequence> DataSet;
    typedef map<string, ofVideoPlayer> PlayerSet;
    static void addPath(string path);
    
    //this is very very heavy prosess;
    static bool loadData();
    static DataSet datas;
    static PlayerSet p_datas;
    
private:
    
};

#endif /* SoundReactiveDataSetManager_hpp */
