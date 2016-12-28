//
//  CountDownManager.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/12/16.
//
//

#ifndef CountDownManager_hpp
#define CountDownManager_hpp

#include <stdio.h>
#include "ofMain.h"

class Timer{
private:
    bool _done;
    time_t _timing;
    
public:
    Timer(time_t ti);
    bool isTiming(time_t t);
    bool isDone(){return _done;};
};

template <typename res>
class CountDownManager{
private:
    typedef shared_ptr<res> res_p;
    typedef pair<Timer, res_p> timer;
    vector<timer> timers;
    
public:
    void setTimer(time_t t, res_p r){
        Timer timer = Timer(t);
        if (!timer.isDone()){
            auto p = pair<Timer, res_p> (timer, r);
            timers.push_back(p);
        }
    }
    
    res_p checkTiming(){
        time_t now = time(NULL);
        for(int i = 0; i < timers.size(); i ++){
            if(timers[i].first.isTiming(now)){
                return timers[i].second;
            }
        }
        return res_p();
    }

};


#endif /* CountDownManager_hpp */
