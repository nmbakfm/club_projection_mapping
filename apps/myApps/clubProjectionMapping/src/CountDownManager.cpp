//
//  CountDownManager.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/12/16.
//
//

#include "CountDownManager.hpp"

Timer::Timer(time_t ti) {
    _timing = ti;
    if (difftime(ti, time(0)) < 0)
        _done = false;
    else
        _done = true;
}

bool Timer::isTiming(time_t t){
    if( _done )return false;
    
    if (difftime(_timing, t) > 0){
        _done = true;
        return true;
    }
}
