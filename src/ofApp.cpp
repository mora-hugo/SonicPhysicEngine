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
    //ringButton.addListener(this, &ofApp::ringButtonPressed);
    fireballVolume.addListener(this, &ofApp::FireballVolumeChanged);

    //here we are setting up all the buttons  
    gui.setup(); // most of the time you don't need a name
    //gui.add(filled.setup("fill", false));
    gui.add(radius.setup("radius", 40, 10, 300));
    gui.add(center.setup("center", {ofGetWidth()*.5, ofGetHeight()*.5}, {0, 0}, {ofGetWidth(), ofGetHeight()}));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(circleResolution.setup("circle res", 50, 3, 90));
    //gui.add(twoCircles.setup("two circles"));
    //gui.add(ringButton.setup("ring"));
    gui.add(launchBall.setup("Projectile de base | C"));
    gui.add(launchFireBall.setup("FireBall | V"));
    gui.add(fireballVolume.setup("Fireball Volume", 1.0f, 0.1f, 1.0f));
    gui.add(launchthirdBall.setup("Projectile n3 | B"));
    gui.add(launchFourthBall.setup("Projectile n4 | N"));
    gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    
    bHide = false;
    FireballSound.load("fireball_sound.wav");
    
    //ring.load("ring.wav");
}

//--------------------------------------------------------------
void ofApp::exit(){
    //ringButton.removeListener(this, &ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int &circleResolution){
    ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
/*void ofApp::ringButtonPressed(){
    ring.play();
}*/

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
	
    /*if(filled){
        ofFill();
    }else{
        ofNoFill();
    }*/

    ofNoFill();

    

    ofSetColor(color);
    /*if(twoCircles){
        ofDrawCircle(center->x-radius*.5, center->y, radius );
        ofDrawCircle(center->x+radius*.5, center->y, radius );
    }else{
        ofDrawCircle(center, radius );
    }*/

    ofDrawCircle(center, radius );

    ofDrawCircle(TargetPositionX,TargetPositionY, 30);

    ofDrawLine(center->x,center->y, (mouseX), (mouseY));

    //Clic sur le GUI
    if(launchBall)
    {
        Particle * p = particleSystem.AddParticle(new Particle(20,1, Vector3D(center->x,center->y),Vector3D(TargetPositionX - center->x, TargetPositionY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    
    if(launchFireBall)
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(TargetPositionX - center->x, TargetPositionY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }

    if(launchthirdBall)
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(TargetPositionX - center->x, TargetPositionY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }

    if(launchFourthBall)
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(TargetPositionX - center->x, TargetPositionY -center->y), Vector3D(0,9.8), 20));
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

    //sauvegarde
    if(key == 'h'){
        bHide = !bHide;
    }
    else if(key == 'o'){
        gui.saveToFile("settings.xml");
    }
    else if(key == 'p'){
        gui.loadFromFile("settings.xml");
    }

    //viseur
    else if(key == 't'){
        TargetPositionX = mouseX;
        TargetPositionY = mouseY;
    }
    
    //Touches
    else if(key == 'c'){
        Particle * p = particleSystem.AddParticle(new Particle(20,1, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    else if(key == 'v')
    {
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    else if(key == 'b'){
        //mettre la particule N3
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    else if(key == 'n'){
        //mettre la particule N4
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,1, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,9.8), 20));
        p->Setup();
        FireballSound.play();
    }
    
    //Deplacement
    else if(key == 'w' || key == 'z'){
        center.setup("center", {center->x, center->y-5}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    else if(key == 'a' || key == 'q')
    {
        center.setup("center", {center->x-5, center->y}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    else if(key == 's'){
        center.setup("center", {center->x, center->y+5}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    else if(key == 'd')
    {
        center.setup("center", {center->x+5, center->y}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    
    //defaut
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
