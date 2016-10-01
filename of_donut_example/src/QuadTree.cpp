#include "QuadTree.h"


void QuadTree::init(AABB _bound, int _level, int _max) {
    //ctor
    bound = _bound;
    level = _level;
    maxLevel = _max;
    divided = false;
    cout<<"Making the tree: "<<level<<" "<<maxLevel<<endl;
}

bool QuadTree::insertPt(ofVec2f pt) {
    cout<<"-Inserting a point: "<<level<<" "<<maxLevel<<endl;
    if(!bound.containsPt(pt.x, pt.y)) {
        cout<<"--Not Here"<<endl;
        return false;
    }
    
    if(level == maxLevel) {
        cout<<"-Add the point! Yay"<<endl;
        pts.push_back(pt);
        return true;
    }
    
    if(!divided) {
        subdivide();
        divided = true;
    }
    
    if(cNW->insertPt(pt)) {
        cout<<"--NW?"<<endl;
        return true;
    }
    if(cNE->insertPt(pt)) {
        cout<<"--NE?"<<endl;
        return true;
    }
    if(cSW->insertPt(pt)) {
        cout<<"--SW?"<<endl;
        return true;
    }
    if(cSE->insertPt(pt)) {
        cout<<"--SE?"<<endl;
        return true;
    }
    
    return false;
};

void QuadTree::draw() {
    bound.draw();
    cNW->draw();
    cNE->draw();
    cSW->draw();
    cSE->draw();
    
}

bool QuadTree::subdivide() {
    cout<<"Subdividing: "<<level<<" "<<maxLevel<<endl;
    
    
    AABB bNW, bNE, bSW, bSE;
    
    bNW.x = bound.x - bound.w / 2;
    bNW.y = bound.y + bound.h / 2;
    bNW.w = bound.w / 2;
    bNW.h = bound.h / 2;
    
    bNE.x = bound.x + bound.w / 2;
    bNE.y = bound.y + bound.h / 2;
    bNE.w = bound.w / 2;
    bNE.h = bound.h / 2;
    
    bSW.x = bound.x - bound.w / 2;
    bSW.y = bound.y - bound.h / 2;
    bSW.w = bound.w / 2;
    bSW.h = bound.h / 2;
    
    bSE.x = bound.x + bound.w / 2;
    bSE.y = bound.y - bound.h / 2;
    bSE.w = bound.w / 2;
    bSE.h = bound.h / 2;
    
    // cNW->init(bNW, level+1, maxLevel);
    //cout<<"Brakes before here"<<endl;
    //cNE->init(bNE, level+1, maxLevel);
    // cSW->init(bSW, level+1, maxLevel);
    //cSE->init(bSE, level+1, maxLevel);
    
    QuadTree qNW, qNE, qSE, qSW;
    
    qNW.init(bNW, level+1, maxLevel);
    cout<<"Brakes before here"<<endl;
    qNE.init(bNE, level+1, maxLevel);
    qSW.init(bSW, level+1, maxLevel);
    qSE.init(bSE, level+1, maxLevel);
    
    cNW = &qNW;
    cNE = &qNE;
    cSW = &qSW;
    cSE = &qSE;
    
    cout<<"Done : "<<level<<" "<<maxLevel<<endl;
    
};

std::vector<ofVec2f> QuadTree::queryRange(AABB range) {
    std::vector<ofVec2f> ptsInRange;
    
    if(!bound.checkIntersection(range))
        return ptsInRange;
    
    for(int i = 0; i<pts.size(); i++) {
        if(bound.containsPt(pts[i].x, pts[i].y))
            ptsInRange.push_back(pts[i]);
    }
    
    if(cNW == NULL)
        return ptsInRange;
    
    add_vector(ptsInRange, cNW->queryRange(range));
    add_vector(ptsInRange, cNE->queryRange(range));
    add_vector(ptsInRange, cSW->queryRange(range));
    add_vector(ptsInRange, cSE->queryRange(range));
    
    // ptsInRange.push_back(cNE->queryRange(range));
    
    return ptsInRange;
    
};

void QuadTree::add_vector(std::vector<ofVec2f>& base, std::vector<ofVec2f> toAdd) {
    base.insert(base.begin(), toAdd.begin(), toAdd.end());
};