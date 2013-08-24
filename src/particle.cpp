//
//  particle.cpp
//  ton_isosphere
//
//  Created by Christian Gwiozda on 23.08.13.
//
//

#include "particle.h"

Particle::Particle(ofVec3f pos_, ofImage* png_) {
    
    pos = pos_;
    
    png = png_;
    
    life = 500;
    
    png->resize(50, 50);
}

void Particle::draw() {


    ofPushMatrix();
    ofSetColor(255,30);
    ofEllipse(pos, 5, 5);
    //png->draw(pos.x+25, pos.y+25, pos.z);
    
    ofPopMatrix();
    
}


void Particle::update() {
    
    
}