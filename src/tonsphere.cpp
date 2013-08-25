//
//  tonsphere.cpp
//  ton_isosphere
//
//  Created by Christian Gwiozda on 17.08.13.
//
//

#include "tonsphere.h"


Tonsphere::Tonsphere() {
    
    returnForce = 0.0008;
    mass = 50;
    friction = 0.97;
    counter = 0.0;
    midiTrigger = 15000;
    color = 0;
    
    //basic w20
    vector<ofVec3f> base_ico;
    
    float s = 80;
    float t = ((1.0 + sqrt(5.0)) / 2) *s;
    
    base_ico.push_back(ofVec3f(-s, t, 0));
    base_ico.push_back(ofVec3f(s, t, 0));
    base_ico.push_back(ofVec3f(-s, -t, 0));
    base_ico.push_back(ofVec3f(s, -t, 0));
    
    base_ico.push_back(ofVec3f(0, -s, t));
    base_ico.push_back(ofVec3f(0, s, t));
    base_ico.push_back(ofVec3f(0, -s, -t));
    base_ico.push_back(ofVec3f(0, s, -t));
    
    base_ico.push_back(ofVec3f(t, 0, -s));
    base_ico.push_back(ofVec3f(t, 0, s));
    base_ico.push_back(ofVec3f(-t, 0, -s));
    base_ico.push_back(ofVec3f(-t, 0, s));
    
    int ico_index[] = {0,11,5,0,5,1,0,1,7,0,7,10,0,10,11,
        1,5,9,5,11,4,11,10,2,10,7,6,7,8,1,
        3,9,4,3,4,2,3,2,6,3,6,8,3,8,9,
        4,9,5,2,4,11,6,2,10,8,6,7,9,8,1
    };
    
    ico_sphere.setMode(OF_PRIMITIVE_TRIANGLES);
    outerMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    
    for (int i = 0; i < 60; i+=3) {
        ico_sphere.addVertex(base_ico[ico_index[i]]);
        ico_sphere.addVertex(base_ico[ico_index[i+1]]);
        ico_sphere.addVertex(base_ico[ico_index[i+2]]);
        
    }
    
    refine_mesh();
    
    png.loadImage("particle.png");
    
}

void Tonsphere::setNormals(ofMesh* mesh_) {
    
        mesh_->clearNormals();
    
    for (int i = 0; i< mesh_->getNumVertices(); i++) {
    
            ofVec3f temp = mesh_->getVertex(i);
    
           //temp = ofVec3f(0,0,0)+temp;
    
            temp.normalize();
    
           mesh_->addNormal(temp);
    
    
    
       }
    
//    mesh_->clearNormals();
//    
//    for (int i = 1; i< mesh_->getNumVertices(); i+=3) {
//        
//        ofVec3f temp = mesh_->getVertex(i);
//        ofVec3f tempA = temp - mesh_->getVertex(i-1) ;
//        ofVec3f tempB = temp - mesh_->getVertex(i+1);
//        
//        temp = tempA.getCrossed(tempB);
//        
//        temp.normalize();
//        
//        mesh_->addNormal(temp);
//        mesh_->addNormal(temp);
//        mesh_->addNormal(temp);
//        
//        
//    }
    
    
}

void Tonsphere::refine_mesh() {
    
    new_index.clear();
    
    new_mesh.clear();
    
    new_vertex.clear();
    
    ico_sphere.clearColors();
    
    
    for (int i = 1; i < ico_sphere.getNumVertices(); i+=3) {
        
        ofVec3f temp1 = ico_sphere.getVertex(i-1);
        temp1 /= sqrt((temp1.x*temp1.x+temp1.y*temp1.y+temp1.z*temp1.z)) ;
        temp1 *= 100;
        
        ofVec3f temp2 = ico_sphere.getVertex(i);
        temp2 /= sqrt((temp2.x*temp2.x+temp2.y*temp2.y+temp2.z*temp2.z)) ;
        temp2 *= 100;
        
        ofVec3f temp3 = ico_sphere.getVertex(i+1);
        temp3 /= sqrt((temp3.x*temp3.x+temp3.y*temp3.y+temp3.z*temp3.z)) ;
        temp3 *= 100;
        
        ofVec3f p1 =  ((temp1+temp2)/2);
        p1 /= sqrt(p1.x*p1.x+p1.y*p1.y+p1.z*p1.z);
        p1 *= 79;
        
        ofVec3f p2 =  ((temp2+temp3)/2);
        p2 /= sqrt(p2.x*p2.x+p2.y*p2.y+p2.z*p2.z);
        p2 *= 79;
        
        ofVec3f p3 =  ((temp3+temp1)/2);
        p3 /= sqrt(p3.x*p3.x+p3.y*p3.y+p3.z*p3.z);
        p3 *= 79;
        
        
        
        check_double(temp1);
        
        check_double(p1);
        
        check_double(p3);
        
        
        check_double(temp2);
        
        check_double(p2);
        
        check_double(p1);
        
        
        check_double(temp3);
        
        check_double(p3);
        
        check_double(p2);
        
        
        
        check_double(p1);
        
        check_double(p2);
        
        check_double(p3);
        
        
        
    }
    
    ico_sphere.clear();
    
    for (int i = 0; i < new_index.size(); i++) {
        
        ico_sphere.addVertex(new_vertex[ new_index[i] ].vertex );
        
        
        
        ico_sphere.addColor(new_vertex[ new_index[i] ].farbe);
        
        
    }
    
    setNormals(&ico_sphere);
    
    
    //set midichannels for better sound
    for (int i = 0; i < new_vertex.size(); i++) {
        new_vertex[i].channel = i%8 ;
    }
    
    gridCopy = new_vertex;
    
    
    
}

void Tonsphere::check_double(ofVec3f vec_) {
    
    // cout << new_vertex.size() << "\n";
    
    
    bool test;
    VertexGrid temp2;
    
    if (new_vertex.empty()) {
        
        VertexGrid temp;
        temp.vertex = vec_;
        temp.vId  = 0;
        temp.velo = ofVec3f(0,0,0);
        new_vertex.push_back(temp);
        new_index.push_back(0);
        
    } else {
        
        test = false;
        
        for (int i = 0; i < new_vertex.size(); i++) {
            
            if (new_vertex[i].vertex == vec_) {
                new_index.push_back(i);
                test = true;
                break;
            } else {
                test = false;
            }
            
        }
        
        
        if (test == false) {
            
            new_index.push_back(new_vertex.size());
            temp2.vertex = vec_;
            temp2.vId =new_vertex.size();
        }
        
    }
    
    
    
    
    new_vertex.push_back(temp2);
    
    
    //    map<ofVec3f,int>::iterator it = new_vertices.find(vec_);
    //    if  ( it != new_vertices.end() ){
    //        new_index.push_back(new_vertices.find(vec_)->second);
    //    } else {
    //        new_index.push_back(new_vertices.size());
    //        new_vertices[vec_] = new_vertices.size();
    //        new_mesh.push_back(vec_);
    //    }
    
    
}

void Tonsphere::draw() {
    
    
    
    //ico_sphere.draw();
    //ofSetColor(255, 255, 255);
    
    ico_sphere.draw();
    
    outerMesh.drawWireframe();
    
    //ico_sphere.drawWireframe();
    
    //    for (int i=0; i < ico_sphere.getNumVertices(); i++) {
    //
    //        ofVec3f aa = ico_sphere.getVertex(i);
    //        ofVec3f bb = ico_sphere.getNormal(i)*12;
    //
    //        ofLine(aa.x, aa.y, aa.z, aa.x+bb.x, aa.y+bb.y, aa.z+bb.z);
    //    }
}


void Tonsphere::update() {
    
    
    
    
    if (ofGetFrameNum()%20 == 0) {
        int ranNum = ofRandom(int(new_vertex.size()));//
        ofVec3f ranVec = new_vertex[ ranNum].vertex;
        ranVec.normalize();
        ranVec *= 10;

        new_vertex[ranNum].velo += ranVec;
    }
    
    
    
    
    for (int i = 0; i < new_index.size(); i++) {
        
        //change mesh, based on finger distance ect.
        
        ofVec3f temp = new_vertex[i].vertex - gridCopy[i].vertex;
        
        float tempDist = temp.lengthSquared();
        if (tempDist > 1) {
            
            float force = ( tempDist) * returnForce;
            temp.normalize();
            temp *= -1;
            temp *= force;
            new_vertex[i].acc +=temp;
        }
        
        //limit velocity
        
        //break velo
        if (new_vertex[i].vertex.lengthSquared() > 60000) {
            new_vertex[i].velo.normalize();
            // new_vertex[i].velo *= 88;
        }
        
        new_vertex[i].velo += new_vertex[i].acc;
        
        new_vertex[i].vertex += new_vertex[i].velo;
        
        
        new_vertex[i].velo *= friction;
        
        
        
        //new_vertex[i].farbe = ofColor::fromHsb(110, 100, 100);
        
        
        
        
        
        
        
        new_vertex[i].acc *= 0;
    }
    
    //nacheinander berechnen damit die force änderungen shcon alle drin sind und es keine lücken zwischen den triangles gibt
    for (int i = 0; i < new_index.size(); i++) {
        //create new Mesh
        ico_sphere.addVertex(new_vertex[ new_index[i] ].vertex );
        
        //  cout << tempCol << "\n";
        float lSquare = new_vertex[new_index[i]].vertex.lengthSquared();
        float tempCol = ofMap(lSquare, 8000, 22340, 0, 255);
        
        //color ohne pitch scale
        //  ico_sphere.addColor(ofColor::fromHsb( 270, 222, tempCol));
        //color mit pitch scale
        
        ico_sphere.addColor(ofColor::fromHsb( color, 142+((new_vertex[new_index[i]].pitch) -71)*7, tempCol));
        
        
        ofVec3f sV;
        ofColor oColor;
        sV = new_vertex[new_index[i]].vertex;
        
        if (lSquare > midiTrigger) {
            sV*= ofRandom(1.10,1.19);
            //sV.normalize();
            //sV*=180;
            
            oColor  = ofColor::fromHsb(color, 88, tempCol-20,35 );
        }else {
        sV.normalize();
        sV*=140;
            
            
            
            oColor = ofColor::fromHsb(color, 111, tempCol-50,0 );
        }
        outerMesh.addVertex(sV);
        outerMesh.addColor(oColor);
        //send midi
        
        sendMidi(&new_vertex[ new_index[i] ], lSquare);
        
        
        
    }
    
    
    
   
    setNormals(&outerMesh);
    setNormals(&ico_sphere);
    
    
    
    
    
    //    for (int i = 0; i < hands->size(); i++) {
    //        for (int j = 0; j < hands->at(i).fingers.size(); j++) {
    //            for (int k = 0; k < new_vertex.size(); k++) {
    //
    //                ofVec3f dir = new_vertex[k].vertex;
    //
    //                dir -= hands->at(i).fingers[j].pos;
    //                ofSetColor(255,255,255);
    //                ofLine(hands->at(i).fingers[j].pos.x, hands->at(i).fingers[j].pos.y,hands->at(i).fingers[j].pos.z, dir.x, dir.y, dir.z);
    //
    //            }
    //        }
    //    }
    
    
    
}


void Tonsphere::sendMidi(VertexGrid* vg_, float ls_) {
    
    if ((!vg_->hover) && (ls_ > midiTrigger)) {
        
        midi->sendNoteOn(vg_->channel, vg_->pitch, 120 );
        vg_->hover = true;
        
        //add Particle
        //partikel.push_back(Particle(vg_->vertex, &png));
    }
    
    if ((vg_->hover) && (ls_ < midiTrigger)) {
        
        midi->sendNoteOff(vg_->channel, vg_->pitch, 120);
        vg_->hover = false;
    }
    
}

void Tonsphere::link_Leap(vector<ofxLeapMotionSimpleHand>* hand_) {
    
    hands = hand_;
}

void Tonsphere::link_midi(ofxMidiOut *midi_) {
    
    midi = midi_;
}

void Tonsphere::addForce(ofVec3f force_) {
    
    
}

void Tonsphere::clearAll() {
    
    outerMesh.clear();
    ico_sphere.clearVertices();
    ico_sphere.clearNormals();
    ico_sphere.clearColors();
    for (int i = 0; i < new_vertex[i].finger_dist; i++) {
        new_vertex[i].finger_dist = 0;
    }
    
}

void Tonsphere::updateParticle() {
    
    for (int i = 0; i < partikel.size(); i++) {
        partikel[i].update();
    }
}


void Tonsphere::drawParticle() {
    
    for (int i = 0; i < partikel.size(); i++) {
        partikel[i].draw();
    }
    
}