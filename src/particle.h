#pragma once

#include "ofMain.h"


class Particle {
    
public:
    
    Particle(ofVec3f, ofImage* );
    
    ofImage* png;
    
    
    void update();
    
    void draw();
    
    float life;
    
    ofVec3f pos;
    ofVec3f velo;
    
    
};
