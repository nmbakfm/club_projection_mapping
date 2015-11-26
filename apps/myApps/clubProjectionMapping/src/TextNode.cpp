//
//  TextNode.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/23.
//
//

#include "TextNode.hpp"

void TextNode::draw(){
    ofPushMatrix();
    
    ofSetColor(255);
    font->drawStringAsShapes(word,0,0);
    ofPopMatrix();
}

int TextNode::getWidth(){
    if(this->word != " "){
        return font->stringWidth(word) + 12;
    }else{
        return font->stringWidth("l");
    }
}