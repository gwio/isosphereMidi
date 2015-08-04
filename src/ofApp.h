#pragma once

#include "ofMain.h"
#include "tonsphere.h"
#include "structs.h"
#include "ofxLeapMotion2.h"
//#include "ofxMidi.h"
#include "ofxUI.h"
#include "ofxTonic.h"

using namespace Tonic;


class ofApp : public ofBaseApp{
    
    ofxTonicSynth synth;
    
    Generator synthA;
    Generator synthB;
    
    ADSR adsr1;
    ADSR adsr2;
    
    ControlGenerator note, midiNote,trigger;
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void exit();
    void audioRequested (float * output, int bufferSize, int nChannels);
    
    ofEasyCam cam;
    
    
    bool drawGrid;
    
    Tonsphere sphere;
    ofLight pointLight;
    ofMaterial material;
    
    ofLight light;
    ofxLeapMotion leap;
    
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
    vector <int> fingersFound;
    
    // ofxMidiOut midiOut;
    
    ofxUICanvas *gui;
    void guiEvent(ofxUIEventArgs &e);
    
    float attDist;
    float attForce;
    float returnForce;
    float friction;
    float midiTrigger;
    float color;
    

    
};
