#include "ofApp.h"
#include "time.h"
#include "Public/Particle/ParticleFireball.h"

//--------------------------------------------------------------
void ofApp::setup(){
    LastFrameTime = clock();
    Particle * myParticle = particleSystem.AddParticle(new Particle(5,Vector3D(50,600),Vector3D(0.2,-1), Vector3D(0,0.00098), 30));
    myParticle->SetColor(ofColor::green);
    particleSystem.AddParticle(new ParticleFireball(50,Vector3D(50,200),Vector3D(0.3,-0.4), Vector3D(0,0.00098), 20));
    
    particleSystem.Setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    FrameLength = clock() - LastFrameTime;
    
    particleSystem.Update(FrameLength);
    
    LastFrameTime = clock();
}

//--------------------------------------------------------------
void ofApp::draw(){
    particleSystem.Draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
