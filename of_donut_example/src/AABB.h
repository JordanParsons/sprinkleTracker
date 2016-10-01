#include <cmath>
#include "ofMain.h"

class AABB {
public:
    float x;
    float y;
    float h;
    float w;
    
    AABB() {}
    
    void init(float _x, float _y, float _w, float _h) {
        x = _x;
        y = _y;
        w = _w;
        h = _h;
    }
    
    bool containsPt(float tx, float ty) {
        if(std::abs(tx-x) > w) {
            return false;
        } else if(std::abs(ty-y) > h) {
            return false;
        }
        return true;
    }
    
    bool checkIntersection(AABB box) {
        return (std::abs(x - box.x) < (w + box.w))&&
        (std::abs(y - box.y) < (h + box.h));
    }
    
    void draw(){
        //cout<<"draw?"<<x<<" "<<y<<" "<<h<<" "<<w<<endl;
        ofRect(x,y,w,h);
    }
};