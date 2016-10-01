#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <cstdlib>
#include "AABB.h"
#include "ofMain.h"

class QuadTree
{
public:
    int maxLevel;
    int level;
    
    std::vector<ofVec2f> pts;
    
    AABB bound;
    bool divided;
    
    QuadTree* cNW;
    QuadTree* cNE;
    QuadTree* cSW;
    QuadTree* cSE;
    
    void init(AABB, int, int);
    bool insertPt(ofVec2f);
    bool subdivide();
    std::vector<ofVec2f> queryRange(AABB);
    void add_vector(std::vector<ofVec2f>&, std::vector<ofVec2f> );
    void draw();
    
};

#endif // QUADTREE_H