//
//  TextNode.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/23.
//
//

#ifndef TextNode_hpp
#define TextNode_hpp

#include <stdio.h>
#include <memory>
#include "ofMain.h"

class TextNode{
private:
    typedef shared_ptr<ofTrueTypeFont> f_p;
    string word;
    f_p font;
public:
    TextNode(string s ,f_p f){this->word = s; this->font = f;}
    void setFont(f_p f){this->font = f;}
    int getWidth();
    int getHeight(){return this->font->stringHeight(word);}
    void draw();
    int offsetX(){return this->getWidth() / 2;}
    int offsetY(){return this->getWidth() / 2;}
    
};

#endif /* TextNode_hpp */