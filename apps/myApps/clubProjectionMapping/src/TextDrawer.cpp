//
//  TextDrawer.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/22.
//
//

#include "TextDrawer.hpp"
#include "Settings.h"

typedef std::shared_ptr<TextDrawer> d_p;

std::shared_ptr<TextDrawer> TextDrawer::Alloc(){
    auto p = std::shared_ptr<TextDrawer>(new TextDrawer());
    p->self = p;
    p->setPosition(ofPoint(0,0));
    return p;
}

shared_ptr<ofTrueTypeFont> TextDrawer::getTrueTypeFont(){
    switch (this->fontType){
        case NormalFontType:
            return Settings::normalFont;
            break;
        case WeddingFontType:
            return Settings::weddingFont;
            break;
        case BirthdayFontType:
            return Settings::birthdayFont;
            break;
    }
    return Settings::normalFont;
}

d_p TextDrawer::setFontType(FontType t){
    auto f = getTrueTypeFont();
    for(auto it = nodes.begin(); it != nodes.end(); it ++){
        it->setFont(f);
    }
    this->fontType = t;
    return self.lock();
}

d_p TextDrawer::setAnimator(shared_ptr<NodeAnimator> a){
    this->base_animator = a;
    updateAnimator();
    return self.lock();
}

void TextDrawer::updateAnimator(){
    this->animator_nodes.clear();
    
    int index[nodes.size()];
    
    for(int i = 0; i < nodes.size(); i ++){
        index[i] = i;
    }
    if(base_animator->isRandom()){
        for(int i = 0; i < nodes.size() * 3; i ++){
            int swap1 = rand() % nodes.size();
            int swap2 = rand() % nodes.size();
            int buf = index[swap1];
            index[swap1] = index[swap2];
            index[swap2] = buf;
        }
    }
    for(int i = 0; i< nodes.size(); i ++){
        auto a = base_animator->clone();
        a->setTimeOffset(index[i] * base_animator->getDiff());
        animator_nodes.push_back(a);
    }
}

d_p TextDrawer::setMessage(string message){
    
    //make Nodes
    nodes.clear();
    for(auto it = message.begin(); it != message.end(); it++){
        char a = *it;
        nodes.push_back(TextNode(string(&a, 1), getTrueTypeFont()));
    }
    this->message = message;
    updateAnimator();
    return self.lock();
}

int TextDrawer::getMessageHeight(){
    int height = 0;
    if(!nodes.empty())height = nodes[0].getHeight();
    return height;
}


int TextDrawer::getMessageWidth(){
    int width = 0;
    for(auto it = nodes.begin(); it != nodes.end(); it++){
        width += it->getWidth();
    }
    return width;
}

void TextDrawer::draw(){
    ofPoint pos =  position;
    auto font = getTrueTypeFont();
    
    int width = getMessageWidth();
    int height = getMessageHeight();
    int offsetX = 0;
    
    ofTranslate(pos.x - width/2, pos.y + height);
    for(int i = 0; i < nodes.size(); i++){
        auto n = nodes[i];
        auto a = animator_nodes[i];
        ofPushMatrix();
            ofTranslate(offsetX, 0);
            ofPushMatrix();
        
                float w = n.getWidth() / 2;
                float h = n.getHeight() / 2;
                ofTranslate( w, -h);
                a->update(currentFrame);
                ofTranslate(-w,  h);
                n.draw();
        
            ofPopMatrix();
            offsetX += n.getWidth();
        ofPopMatrix();
    }
    
}

void TextDrawer::update(){
    if(!this->isDone())this->currentFrame ++;
}

bool TextDrawer::isDone(){
    return this->currentFrame >= this->showEndFrame;
}

void TextDrawer::restart(){
    this->currentFrame = 0;
}