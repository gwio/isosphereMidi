#pragma once

#include "ofMain.h"


struct VertexGrid {
    
    VertexGrid() {
        hover = false;
        finger_dist = 1000000000.0;
        farbe = ofColor::fromHsb(0, 0, 255);
        
        int scale [10] = {0,3,5,7,10, 12,15,17,19,22};
        
        noteScale = scale[ int(ofRandom(10)) ] ;
        note = 0;
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
    int noteScale;
    int note;
    int octave;
    int channel;
};


