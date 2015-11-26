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
#include "Animator.hpp"
#include "TextNode.hpp"
#include "NodeAnimator.hpp"

typedef enum {
    NormalFontType = 0,
    WeddingFontType = 1,
    BirthdayFontType = 2
} FontType;

class TextDrawer;


class TextDrawer{
private:
    typedef std::shared_ptr<TextDrawer> d_p;
public:
    
    static std::shared_ptr<TextDrawer> Alloc();
    void draw();
    void update();
    void restart();
    bool isDone();
    
    d_p setAnimator(shared_ptr<NodeAnimator> ani);
    
    d_p setMessage(string message);
    string getMessage(){return this->message;}
    
    d_p setFontType(FontType t);
    FontType getFontType(){return this->fontType;}
    
    d_p setPosition(ofPoint p){this->position = p; return self.lock();}
    ofPoint getPosition(){return this->position;}
    
    
    d_p setTiming(int animationEndFrame = -1, int showEndFrame = -1){
        if(animationEndFrame > 0)this->animeEndFrame = animationEndFrame;
        if(showEndFrame > 0)this->showEndFrame = showEndFrame;
        return self.lock();
    }
    ~TextDrawer(){ ofLogNotice("=========textDrawer '" + this->getMessage() +  "' deallcated========="); }
    
    
    
    
    
private:
    std::vector<TextNode> nodes;
    std::vector<shared_ptr<NodeAnimator> > animator_nodes;
    ofPoint position;
    int getMessageWidth();
    int getMessageHeight();
    std::weak_ptr<TextDrawer> self;
    string message = "";
    FontType fontType = NormalFontType;
    TextDrawer(){};
    shared_ptr<ofTrueTypeFont> getTrueTypeFont();
    int animeEndFrame;
    int currentFrame = 0;
    int showEndFrame;
    shared_ptr<NodeAnimator> base_animator = shared_ptr<NodeAnimator>(new NodeAnimator());
    void updateAnimator();
};

typedef TextDrawer MessageDrawer;

#endif /* TextDrawer_hpp */
