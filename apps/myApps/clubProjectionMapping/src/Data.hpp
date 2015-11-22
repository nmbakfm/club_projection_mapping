//
//  Data.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/18.
//
//

#ifndef __club_Movie_Data_hpp
#define __club_Movie_Data_hpp

#include <stdio.h>
#include <string>
#include <memory>


typedef enum {
    MovieTypeNormal = 0,
    MovieTypeZima = 1,
    MovieTypeBirthDay = 2,
    MovieTypeWedding = 3,
    MovieTypeSoundReactive = 4,
} MovieType;

class MovieData{
private:
    std::string file_path;
    MovieType movie_type;
    int endframe = 0;
    
public:
    //settergetterのみなのでめんどくさいのでヘッダに実装書く奴
    MovieData(std::string _file_path, MovieType _movie_type){
        this->movie_type = _movie_type;
        this->file_path = _file_path;
    };
    //setter
    void setEndFrameForSoundReactPlayer(int _end_frame){
        if(_end_frame <= 0 )return;
        this->endframe = _end_frame;
        this->movie_type = MovieTypeSoundReactive;
    }
    
    //getter
    std::string getFilePath(){return this->file_path;}
    //if movie has a end framedata, that is soundreactive
    MovieType getMovieType(){return this->movie_type;}
    bool isSoundReactive(){return endframe > 0;}
    int getEndFrame(){return endframe;}
};

#endif /* Data_hpp */
