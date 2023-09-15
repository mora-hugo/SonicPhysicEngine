#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    p1 = Particle(5,Vector3D(50,50),Vector3D(5,0));
    p2 = Particle(10,Vector3D(20,20),Vector3D(2,0));

    
    p1.SetColor(ofColor::aqua);
    p2.SetColor(ofColor::red);
}

//--------------------------------------------------------------
void ofApp::update(){
    p1.Update();
    p2.Update();

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
