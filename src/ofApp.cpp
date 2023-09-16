#include "ofApp.h"
#include "time.h"

//--------------------------------------------------------------
void ofApp::setup(){
    LastFrameTime = clock();
    
    p1 = Particle(5,Vector3D(50,50),Vector3D(1,0), Vector3D(0,0.00098), 30);
    p2 = Particle(10,Vector3D(20,20),Vector3D(1,0),Vector3D(0,0.00098),10);
    
    p1.SetColor(ofColor::aqua);
    p2.SetColor(ofColor::red);
}

//--------------------------------------------------------------
void ofApp::update(){
    FrameLength = clock() - LastFrameTime;
    
    p1.Update(FrameLength);
    p2.Update(FrameLength);
    
    LastFrameTime = clock();
}

//--------------------------------------------------------------
void ofApp::draw(){
    p1.Draw();
    p2.Draw();

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
