

#ifndef __ton_isosphere__tonsphere__
#define __ton_isosphere__tonsphere__

#include "ofMain.h"

#include "structs.h"

#include "ofxLeapMotion2.h"

#include "ofxMidi.h"

#include "particle.h"



class Tonsphere {
  
public:
    Tonsphere();
    
    vector<VertexGrid> new_vertex;

    void draw();
    
    void update();
    
    void setNormals(ofMesh*);
    
    void refine_mesh();

    ofMesh ico_sphere;
    
    void check_double(ofVec3f);
    
    vector<int> new_index;
    
    vector<ofVec3f> new_mesh;
    float counter;
    
    vector<VertexGrid> gridCopy;

    vector<ofxLeapMotionSimpleHand>* hands;

    void link_Leap(vector<ofxLeapMotionSimpleHand>* hand_);
    
    void link_midi(ofxMidiOut* midi);
    
    float mass;
    
    void addForce(ofVec3f);
    
    void clearAll();
    
    ofxMidiOut* midi;
    
    void sendMidi(VertexGrid*, float);
    
    ofImage png;
    
    vector<Particle> partikel;
    
    void updateParticle();
    
    void drawParticle();
    
    
    float returnForce;
    
    float friction;
    
    float midiTrigger;
    
    float color;
    
    ofMesh outerMesh;
    
};



#endif /* defined(__ton_isosphere__tonsphere__) */
