#pragma once

#include "ofMain.h"


struct VertexGrid {
    
    VertexGrid() {
        hover = false;
        finger_dist = 1000000000.0;
        farbe = ofColor::fromHsb(0, 0, 255);
        
        int scale [7] = {0,2,3,5,7,9,10};
        
        pitch = 71 +  scale[ int(ofRandom(7)) ] ;
        channel = 0;
        velo = ofVec3f(0,0,0);
        acc = ofVec3f(0,0,0);
    }
    ofVec3f vertex;
    int vId;
    ofColor farbe;
    ofVec3f acc;
    ofVec3f velo;
    bool hover;
    float finger_dist;
    int pitch;
    int channel;
};


