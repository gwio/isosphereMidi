#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    attDist = 140;
    attForce = 0.006;
    friction = 0.97;
    returnForce = 0.0008;
    midiTrigger = 15000;
    color = 0;
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
    
    gui = new ofxUICanvas();
    gui->setFontSize(OFX_UI_FONT_LARGE, 8);
    gui->setFontSize(OFX_UI_FONT_MEDIUM, 8);
    gui->setFontSize(OFX_UI_FONT_SMALL, 8);
    
    gui->addWidgetDown(new ofxUILabel("Physics", OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUISlider("attDist", 10, 300,attDist, 200, 16));
    
    ofxUISlider *w =  (ofxUISlider*) gui->addWidgetDown(new ofxUISlider("attForce", 0.001, 0.007, attForce, 200, 16));
    w->setLabelPrecision(3);
    
    
    w =  (ofxUISlider*) gui->addWidgetDown(new ofxUISlider("returnForce", 0.0001, 0.0012, returnForce, 200, 16));
    w->setLabelPrecision(4);
    
    w =  (ofxUISlider*) gui->addWidgetDown(new ofxUISlider("friction", 0.50, 1.10, friction, 200, 16));
    w->setLabelPrecision(2);
    
    gui->addSpacer();
    gui->addWidgetDown(new ofxUILabel("Midi", OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUISlider("MidiDist", 5000, 25000,midiTrigger, 200, 16));
    
    gui->addSpacer();
    gui->addWidgetDown(new ofxUILabel("Visual", OFX_UI_FONT_SMALL));
    gui->addWidgetDown(new ofxUISlider("Color", 0, 255,color, 200, 16));
    
    
    gui->autoSizeToFitWidgets();
    gui->setTheme(OFX_UI_THEME_COOLPURPLE);
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    
    
    leap.open();
    ofSetVerticalSync(false);
    
    midiOut.openPort(0);
    
    ofSetSmoothLighting(true);
    ofSetFrameRate(60);
    ofSetSmoothLighting(true);
    ofEnableAlphaBlending();
    ofDisableAntiAliasing();
    
    material.setShininess(20);
    material.setAmbientColor(155);
    material.setDiffuseColor(155);
    material.setSpecularColor(ofColor::fromHsb(33,222,155));
    
    
    
    light.setAmbientColor(ofColor::fromHsb(30, 111, 255));
    light.setDiffuseColor(ofColor::fromHsb(33,222,255));
    light.setSpecularColor(ofColor(120,120,120));
    light.setPosition(0,400,600);
    
    cam.setDistance(300);
    
    
    sphere.link_Leap(&simpleHands);
    sphere.link_midi(&midiOut);
    
   }

//--------------------------------------------------------------
void ofApp::update(){
    
    
    sphere.clearAll();
    
    fingersFound.clear();
    
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -180, 180);
		leap.setMappingY(90, 490, -180, 180);
        leap.setMappingZ(-150, 150, -180, 180);
        

        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};

        for(int i = 0; i < simpleHands.size(); i++){
            
                 for (int f=0; f<5; f++) {
                     
                        int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                     
                    // ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp; // metacarpal
                   //  ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip; // proximal
                     //ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip; // distal
                     ofPoint pt = simpleHands[i].fingers[ fingerTypes[f] ].tip; // fingertip
                
                //cout << simpleHands[i].fingers.size() << "\n";
                //store fingers seen this frame for drawing
                fingersFound.push_back(id);
                 }
            
        }
    }
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};

    for (int i = 0; i < simpleHands.size(); i++) {
            for (int f=0; f<5; f++) {

            ofPushMatrix();
            ofVec3f tempPos = simpleHands[i].fingers[ fingerTypes[f] ].tip;
            ofSetColor(255, 255, 255);
            //ofVertex(simpleHands[i].fingers[j].pos);
            // ofEllipse(tempPos.x, tempPos.y, tempPos.z, 5, 5);
            ofPopMatrix();
            
            
            ofVec3f finger = simpleHands[i].fingers[ fingerTypes[f] ].tip;
            for (int k = 0; k < sphere.new_vertex.size(); k++) {
                
                
                ofVec3f dir;
                dir = finger - sphere.new_vertex[k].vertex;
                
                float dist = dir.length();
                
                
                
                // cout << dist << "\n";
                
                
                
                
                if (dist < attDist) {
                    
                    //ofEllipse(sphere.new_vertex[k].vertex,6,6);
                    dir.normalize();
                    float force = (attDist -  dist) *attForce;
                    dir*= force;
                    sphere.new_vertex[k].acc += dir;
                    
                    
                    
                    
                    
                }
            }
            
            
        }
    }
    
    
    sphere.update();
    sphere.updateParticle();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0, 0, 0);
    cam.begin();
    ofEnableLighting();
    light.enable();
    material.begin();
    
    
    ofPushMatrix();
    //ofRotate(ofGetElapsedTimef()*10, 0.5, 1, 0.5);
    ofEnableDepthTest();
    
    sphere.draw();
    
    ofSetColor(66,46);
    //ofDisableDepthTest();
    sphere.drawParticle();
    
    ofPopMatrix();
    
    
    if (drawGrid) {
        ofDrawGrid();
    }
    
    fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};

    
    for (int i = 0; i < simpleHands.size(); i++) {
            for (int f=0; f<5; f++) {

            ofPushMatrix();
            ofSetColor(255, 255, 255);
            ofEllipse(simpleHands[i].fingers[ fingerTypes[f] ].tip , 5, 5);
            ofPopMatrix();
            }
        
    }
    
    
    
    cam.end();
    light.disable();
    material.end();
    
    ofDisableDepthTest();
    string fpsStr = "fps: "+ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(fpsStr, ofGetWidth()-100,100);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case 'G':
            drawGrid = !drawGrid;
            break;
            
        case 'r':
            sphere.refine_mesh();
            break;
            
            
        case 's':
            ofSaveFrame();
            break;
            
        case 'g':
            gui->toggleVisible();
            break;
            
            case 'f':
            ofToggleFullscreen();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
    
}

//____________________

void ofApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();
	
	if(name == "attDist")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		attDist = slider->getScaledValue();
	} else if(name == "attForce")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		attForce = slider->getScaledValue();
	} else if(name == "returnForce")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		returnForce = slider->getScaledValue();
        sphere.returnForce = returnForce;
	} else if(name == "friction")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		friction = slider->getScaledValue();
        sphere.friction = friction;
	} else if(name == "MidiDist")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		midiTrigger = slider->getScaledValue();
        sphere.midiTrigger = midiTrigger;
	} else if(name == "Color")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		color = slider->getScaledValue();
        sphere.color = int(color);
	}
}

