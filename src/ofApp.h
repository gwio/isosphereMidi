#pragma once

#include "ofMain.h"
#include "tonsphere.h"
#include "structs.h"
#include "ofxLeapMotion2.h"
#include "ofxMidi.h"
#include "ofxUI.h"

class ofApp : public ofBaseApp{
    
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
    
    ofEasyCam cam;
    
    
    bool drawGrid;
    
    Tonsphere sphere;
    ofLight pointLight;
    ofMaterial material;
    
    ofLight light;
    ofxLeapMotion leap;
    
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
	vector <int> fingersFound;
    
    ofxMidiOut midiOut;
    
    ofxUICanvas *gui;
	void guiEvent(ofxUIEventArgs &e);
    
    float attDist;
    float attForce;
    float returnForce;
    float friction;
    float midiTrigger;
    float color;
    

    
};
