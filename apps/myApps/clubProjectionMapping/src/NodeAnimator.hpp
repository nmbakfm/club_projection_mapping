//
//  NodeAnimator.hpp
//  clubProjectionMapping
//
//  Created by KamedaKei on 2015/11/23.
//
//

#ifndef NodeAnimator_hpp
#define NodeAnimator_hpp

#include <stdio.h>
#include "Animator.hpp"

class TextNode;


class NodeAnimator{
protected:
    int timeOffset = 0;
public:
    virtual void update(int frame){};
    virtual int getLength(){return 0;};
    virtual int getDiff(){return 2;};
    virtual bool isRandom(){return false;};
    virtual shared_ptr<NodeAnimator> clone(){return shared_ptr<NodeAnimator>(new NodeAnimator());}
    void setTimeOffset(int timeOffset){this-> timeOffset = timeOffset;}
};

class SpinIn : public NodeAnimator{
public:
    static shared_ptr<NodeAnimator> Alloc(){
        return shared_ptr<NodeAnimator>(new SpinIn());
    }
    void update(int frame);
    int getLength(){return length;}
    shared_ptr<NodeAnimator> clone(){return shared_ptr<NodeAnimator>(new SpinIn());};
private:
    SpinIn(){}
    const int length = 15;
    shared_ptr<Animator>ani = LinerAnimator::Alloc();
};



class FastDrop : public NodeAnimator{
public:
    static shared_ptr<NodeAnimator> Alloc(){
        return shared_ptr<NodeAnimator>(new FastDrop());
    }
    void update(int frame);
    int getLength(){return length;}
    shared_ptr<NodeAnimator> clone();
private:
    FastDrop(){}
    const int length = 30;
    shared_ptr<Animator>ani = LinerAnimator::Alloc();
};


class ScaleIn : public NodeAnimator{
public:
    static shared_ptr<NodeAnimator> Alloc(){
        return shared_ptr<NodeAnimator>(new ScaleIn());
    }
    void update(int frame);
    int getDiff(){return 1;};
    int getLength(){return length;}
    bool isRandom(){return true;};
    shared_ptr<NodeAnimator> clone();
private:
    ScaleIn(){}
    const int length = 10;
    shared_ptr<Animator>ani = LinerAnimator::Alloc();
};




#endif /* NodeAnimator_hpp */
