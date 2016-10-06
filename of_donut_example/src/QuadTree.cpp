//
//  Quadtree.cpp
//  fluidTesting
//
// Jordan C. Parsons <jordancparsons@gmaill.com> @ Iontank
// Copyright (c) 2015 Iontank. All rights reserved.
//

#include "Quadtree.h"

Quadtree::Quadtree(){
    nw = NULL;
    ne = NULL;
    sw = NULL;
    sw = NULL;
    particles = vector<Sprinkle*>();
}

Quadtree::Quadtree(int pLevel, ofRectangle pBound){
    nw = NULL;
    ne = NULL;
    sw = NULL;
    sw = NULL;

    bounds = AABB(pBound.getTopLeft(), ofVec2f(pBound.getWidth(), pBound.getHeight()));
    level = pLevel;
    particles = vector<Sprinkle*>();
}

Quadtree::Quadtree(int pLevel, ofVec2f tl, ofVec2f dims){
    nw = NULL;
    ne = NULL;
    sw = NULL;
    sw = NULL;
    
    bounds = AABB(tl, dims);
    level = pLevel;
    particles = vector<Sprinkle*>();
}

Quadtree::Quadtree(int pLevel, AABB pBound){
    nw = NULL;
    ne = NULL;
    sw = NULL;
    sw = NULL;
    
    bounds = pBound;
    level = pLevel;
    particles = vector<Sprinkle*>();
}

Quadtree::~Quadtree(){
    if(hasChildren == true){
        delete nw;
        delete ne;
        delete sw;
        delete se;
    }
    
    particles.clear();
}

void Quadtree::clear(){
    particles.clear();
}

bool Quadtree::insert(Sprinkle *p){
    //If the particle isn't in this node, return false
    if(!bounds.inside(p->getPos())){
        return false;
    }
    //if this node is at the max level, or this node isnt full yet add it
    if(particles.size() < QT_MAX_PARTICLES || level >= QT_MAX_LEVELS){
        particles.push_back(p);
        return true;
    }
    //Divide the node if it isn't already
    if(!hasChildren){
        subdivide();
    }
    //Check all the children and insert in whatever one contains it
    if(ne->insert(p)){
        return true;
    }
    if(sw->insert(p)){
        return true;
    }
    if(se->insert(p)){
        return true;
    }
    if(nw->insert(p)){
        return true;
    }
    //Something is wrong, it wasnt inserted (overflow)
    return false;
}

bool Quadtree::insertVec(ofVec2f *p){
    //If the particle isn't in this node, return false
    if(!bounds.inside(*p)){
        return false;
    }
    //if this node is at the max level, or this node isnt full yet add it
    if(locations.size() < QT_MAX_PARTICLES || level >= QT_MAX_LEVELS){
        locations.push_back(p);
        return true;
    }
    //Divide the node if it isn't already
    if(!hasChildren){
        subdivide();
    }
    //Check all the children and insert in whatever one contains it
    if(ne->insertVec(p)){
        return true;
    }
    if(sw->insertVec(p)){
        return true;
    }
    if(se->insertVec(p)){
        return true;
    }
    if(nw->insertVec(p)){
        return true;
    }
    //Something is wrong, it wasnt inserted (overflow)
    return false;
}

void Quadtree::subdivide(){
    hasChildren = true;
    int newH = bounds.getHeight()/2;
    int newW = bounds.getWidth()/2;

    ofVec2f dims = ofVec2f(newW, newH);
    ofVec2f corner = bounds.getTopLeft();
    //Establish the boundries of the child nodes, based on compas directions
    nw = new Quadtree(level+1, AABB(corner, dims));
    ne = new Quadtree(level+1, AABB(ofVec2f(corner.x+newW, corner.y), dims));
    sw = new Quadtree(level+1, AABB(ofVec2f(corner.x, corner.y+newH), dims));
    se = new Quadtree(level+1, AABB(ofVec2f(corner.x+newW, corner.y+newH), dims));
}

vector<ofVec2f*> Quadtree::queryArea(AABB r){
    
     vector<ofVec2f*> contained = vector<ofVec2f*>();
     
     if(!bounds.intersects(r)){
     return contained;
     }
     
     for(int i = 0; i < locations.size(); i++){
         if(r.inside(*locations[i])){
             contained.push_back(locations[i]);
         }
     }
     
     if(!hasChildren)
         return contained;
     
     vector<ofVec2f*> stuff = ne->queryArea(r);
     contained.insert(contained.end(), stuff.begin(), stuff.end());
     stuff = nw->queryArea(r);
     contained.insert(contained.end(), stuff.begin(), stuff.end());
     stuff = se->queryArea(r);
     contained.insert(contained.end(), stuff.begin(), stuff.end());
     stuff = sw->queryArea(r);
     contained.insert(contained.end(), stuff.begin(), stuff.end());
     
     return contained;
    
}

void Quadtree::draw(){
    //draw a nice rectangle

    ofRect(bounds.tl, bounds.getWidth(), bounds.getHeight());
    
    if(!hasChildren)
        return;
    
    nw->draw();
    ne->draw();
    sw->draw();
    se->draw();
}







