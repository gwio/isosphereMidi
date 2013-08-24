//
//  particle.h
//  ton_isosphere
//
//  Created by Christian Gwiozda on 23.08.13.
//
//

#ifndef __ton_isosphere__particle__
#define __ton_isosphere__particle__

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
#endif /* defined(__ton_isosphere__particle__) */
