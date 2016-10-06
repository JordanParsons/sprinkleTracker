//
//  Quadtree.h
//  fluidTesting
//
// Jordan C. Parsons <jordancparsons@gmaill.com> @ Iontank
// Copyright (c) 2015 Iontank. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "Sprinkle.h"
#define QT_MAX_PARTICLES 1
#define QT_MAX_LEVELS 10
#define QT_NODE_CAPACITY 4

//AABB Rectangle For Tree Nodes
struct AABB{
    ofVec2f tl;
    ofVec2f dims;
    
    AABB(ofVec2f tl = ofVec2f(), ofVec2f dims = ofVec2f()): tl(tl), dims(dims){};
    
    //Is a given point inside
    bool inside(ofVec2f pt) const {
        if( pt.x > tl.x && pt.x < tl.x + dims.x){
            if(pt.y > tl.y && pt.y < tl.y + dims.y){
                return true;
            }
        }
        return false;
    }
    
    int getHeight() const{
        return dims.y;
    }
    
    int getWidth() const{
        return dims.x;
    }
    
    ofVec2f getTopLeft() const{
        return tl;
    }
    
    ofVec2f getTopRight() const {
        return tl + dims;
    }
    
    ofVec2f getCenter() const{
        return ofVec2f(tl.x + dims.x/2, tl.y + dims.y /2);
    }
    
    bool intersects(AABB b) const{
        ofVec2f aMax = this->getTopRight();
        ofVec2f bMax = b.getTopRight();
        ofVec2f bMin = b.getTopLeft();
        
        if(aMax.x < bMin.x) return false;
        if(aMax.y < bMin.y) return false;
        
        if(tl.x > bMax.x) return false;
        if(tl.y > bMax.y) return false;
        
        return true;
    }
    
};

class Quadtree {
private:
    //Depth of this node
    int level;
    //Boundry of this node
    AABB bounds;
    //list of particles in this node
    vector<Sprinkle*> particles;
    vector<ofVec2f*> locations;
    //Children of this node
    Quadtree * nw;
    Quadtree * ne;
    Quadtree * se;
    Quadtree * sw;
    //Does this node have children
    bool hasChildren = false;
    
public:
    //Constructors
    Quadtree();
    Quadtree(int pLevel, ofRectangle pBound);
    Quadtree(int pLevel, ofVec2f tl, ofVec2f dims);
    Quadtree(int pLevel, AABB pBound);
    ~Quadtree();
    //Insert Particle into the three
    bool insert(Sprinkle *p);
    bool insertVec(ofVec2f * loc);
    //Create Children for the tree
    void subdivide();
    //Draw this node & its children
    void draw();
    //Wipe the tree, may not be usefull
    void clear();
    //Get any particles in the defined area TBD
    vector<ofVec2f *> queryArea(AABB r);
    
};
