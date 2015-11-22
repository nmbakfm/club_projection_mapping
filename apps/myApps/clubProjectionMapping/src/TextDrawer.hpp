//
//  TextDrawer.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#ifndef TextDrawer_hpp
#define TextDrawer_hpp

#include <stdio.h>
#include <memory>
#include "ofMain.h"


class TextDrawer{
public:
    std::shared_ptr<TextDrawer> Alloc(){
        return std::shared_ptr<TextDrawer>(new TextDrawer());
    }
    
private:
    TextDrawer(){};
    
};

typedef TextDrawer MessageDrawer;

#endif /* TextDrawer_hpp */
