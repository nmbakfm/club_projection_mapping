//
//  Animator.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#ifndef Animator_hpp
#define Animator_hpp

#include <stdio.h>
#include <memory.h>
#include "ofMain.h"


class Animator {
public:
    virtual float Map(float value) = 0;
};

class LinerAnimator : public Animator{
public:
    static shared_ptr<Animator> Alloc(){
        return shared_ptr<Animator>(new LinerAnimator());
    }
    float Map(float value){
        value = MAX(value, 1);
        value = MIN(value, 0);
        return value;
    }
};

#endif /* Animator_hpp */
