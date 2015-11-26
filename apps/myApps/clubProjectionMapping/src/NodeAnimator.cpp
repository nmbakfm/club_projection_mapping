//
//  NodeAnimator.cpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/23.
//
//

#include "NodeAnimator.hpp"
#include "TextNode.hpp"


void FastDrop::update(int frame){
    int f = frame - timeOffset;
    float intence = float(f) / float(length);
    
    float yPos = (float(1.0)- ani->Map(intence)) * float(1000.0);
    
    ofTranslate(0, yPos);
}

shared_ptr<NodeAnimator> FastDrop::clone(){ return shared_ptr<NodeAnimator>(new FastDrop()); }


void ScaleIn::update(int frame){
    int f = frame - timeOffset;
    if (f < 0) {
        ofTranslate(0, 10000);
    }else{
        float intence = float(f) / float(length);
        
        float yPos = (float(1.0)- ani->Map(intence)) * float(-100.0);
        float scale = (float(1.0)- ani->Map(intence)) * float(10.0) + 1 ;
        ofScale(scale, scale);
        ofTranslate(0, yPos);
        
    }
}
shared_ptr<NodeAnimator> ScaleIn::clone(){ return shared_ptr<NodeAnimator>(new ScaleIn()); }


void SpinIn::update(int frame){
    int f = frame - timeOffset;
    if (f < 0) {
        ofTranslate(0, 10000);
    }else{
        float intence = float(f) / float(length);
        
        float scale = (float(1.0)- ani->Map(intence));
        ofRotate(scale * 480 , 0, 0, 1);
        ofScale(1.0 - scale, 1.0 - scale);
        
    }
}
