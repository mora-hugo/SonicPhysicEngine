#include "ofApp.h"
#include "time.h"
#include "Public/Particle/ParticleFireball.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    /*Particle * myParticle = particleSystem.AddParticle(new Particle(5,Vector3D(50,600),Vector3D(0.2,-1), Vector3D(0,0.00098), 30));
    myParticle->SetColor(ofColor::green);
    particleSystem.AddParticle(new ParticleFireball(50,Vector3D(50,200),Vector3D(0.3,-0.4), Vector3D(0,0.00098), 20));*/
    
    particleSystem.Setup();

    //Setup for the interface
    ofSetVerticalSync(true);

    // we add this listener before setting up so the initial circle resolution is correct
    circleResolution.addListener(this, &ofApp::circleResolutionChanged);
    ringButton.addListener(this, &ofApp::ringButtonPressed);
    fireballVolume.addListener(this, &ofApp::FireballVolumeChanged);

    //here we are setting up all the buttons  
    gui.setup(); // most of the time you don't need a name
    gui.add(filled.setup("fill", false));
    gui.add(radius.setup("radius", 140, 10, 300));
    gui.add(center.setup("center", {ofGetWidth()*.5, ofGetHeight()*.5}, {0, 0}, {ofGetWidth(), ofGetHeight()}));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 5, 3, 90));
    gui.add(twoCircles.setup("two circles"));
    gui.add(ringButton.setup("ring"));
    gui.add(launchFireBall.setup("FireBall"));
    gui.add(fireballVolume.setup("Fireball Volume", 1.0f, 0.1f, 1.0f));
    gui.add(launchFromBall.setup("Projectile"));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
    bHide = false;
    FireballSound.load("fireball_sound.wav");
    
    //ring.load("ring.wav");
}

//--------------------------------------------------------------
void ofApp::exit(){
    ringButton.removeListener(this, &ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int &circleResolution){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
    ring.play();
}

void ofApp::FireballVolumeChanged(float &fireballVolume)
{
    FireballSound.setVolume(fireballVolume);
}

//--------------------------------------------------------------
void ofApp::update(){

    //ofGetLastFrameTime();
    //printf ("%lf Seconds.\n", ofGetLastFrameTime());
    FrameTime = ofGetLastFrameTime();
    
    particleSystem.Update(FrameTime);

    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::draw(){
    particleSystem.Draw();

    //test for variable drawn
    //(Les particules sont derrière le décors, JSPP)
    //ofBackgroundGradient(ofColor::white, ofColor::gray);
	
    if(filled){
        ofFill();
    }else{
        ofNoFill();
    }

    

    ofSetColor(color);
    if(twoCircles){
        ofDrawCircle(center->x-radius*.5, center->y, radius );
        ofDrawCircle(center->x+radius*.5, center->y, radius );
    }else{
        ofDrawCircle(center, radius );
    }

    //Clic sur le GUI
    if(launchFireBall)
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(75,-100), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }

    if(launchFromBall)
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(75,-100), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }

    //particleSystem.Setup();
	
    // auto draw?
    // should the gui control hiding?
    if(!bHide){
        gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'h'){
        bHide = !bHide;
    }
    else if(key == 's'){
        gui.saveToFile("settings.xml");
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
    //Touches
    else if(key == 'b'){
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(75,-100), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    else if(key == 't')
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(75,-100), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    else if(key == ' '){
        color = ofColor(255);
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
