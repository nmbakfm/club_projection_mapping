//
//  TextAnimationManager.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#ifndef TextAnimationManager_hpp
#define TextAnimationManager_hpp

#include <stdio.h>
#include <memory>
#include <queue>
#include "ofMain.h"
#include "TextDrawer.hpp"

class TextAnimationManager{
public:
    static shared_ptr< TextAnimationManager > getInstance(){
        if (!_singleton) {
            _singleton = shared_ptr<TextAnimationManager> ( new TextAnimationManager() );
        }
        return _singleton;
    }
    void update();
    void draw();
    shared_ptr<TextDrawer> setNext(shared_ptr<TextDrawer> drawer);
    
private:
    static shared_ptr<TextAnimationManager> _singleton;
    TextAnimationManager(){};
    queue<shared_ptr<TextDrawer> > drawer_queue;
};

#endif /* TextAnimationManager_hpp */
