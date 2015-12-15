//
//  Util.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#ifndef Util_hpp
#define Util_hpp

#include <stdio.h>
#include <memory>
#include "Data.hpp"
#include "ClubVideoPlayer.h"


class Util{
public:
    static std::shared_ptr<BaseVideoPlayer> getPlayerFrom( std::shared_ptr<MovieData> d);
    static string printDate();
};
#endif /* Util_hpp */
