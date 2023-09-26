#include "ofApp.h"
#include "time.h"
#include "Public/Particle/ParticleFireball.h"
#include "Public/Particle/ParticleFirework.h"
#include "Public/Particle/ParticleLaser.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    particleSystem.Setup();

    //Setup for the interface
    ofSetVerticalSync(true);

    //ringButton.addListener(this, &ofApp::ringButtonPressed);
    ProjectileVolume.addListener(this, &ofApp::ProjectileVolumeChanged);

    //here we are setting up all the buttons  
    gui.setup(); // most of the time you don't need a name

    gui.add(center.setup("center", {ofGetWidth()*.5, ofGetHeight()*.5}, {0, 0}, {ofGetWidth(), ofGetHeight()}));
    gui.add(color.setup("color", ofColor(100, 100, 140), ofColor(0, 0), ofColor(255, 255)));
    gui.add(ProjectileVolume.setup("Projectiles Volume", 0.5f, 0.01f, 1.0f));
    gui.add(launchBall.setup("Projectile de base | C"));
    gui.add(launchFireBall.setup("FireBall | V"));
    gui.add(launchthirdBall.setup("Firework | B"));
    gui.add(launchFourthBall.setup("Laser | N"));
    
    bHide = false;

    // Loading sounds
    FireballSound.load("fireball_sound.wav");
    FireworkSound.load("FireworkWhistle.mp3");
    LaserSound.load("laserfire.ogg");
}

//--------------------------------------------------------------
void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int &circleResolution){
    ofSetCircleResolution(circleResolution);
}



void ofApp::ProjectileVolumeChanged(float &ProjectileVolume)
{
    FireballSound.setVolume(ProjectileVolume);
    FireworkSound.setVolume(ProjectileVolume);
    LaserSound.setVolume(ProjectileVolume);
    Volume = ProjectileVolume;
}

//--------------------------------------------------------------
void ofApp::update(){

   
    FrameTime = ofGetLastFrameTime();
    particleSystem.Update(FrameTime);
}

//--------------------------------------------------------------
void ofApp::draw(){
    particleSystem.Draw();

    // draw the GUI
    ofNoFill();
    ofSetColor(color);
    ofDrawCircle(center, 35 );
   // ofDrawCircle(TargetPositionX,TargetPositionY, 30);
    ofDrawLine(center->x,center->y, (mouseX), (mouseY));
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

    //viseur - Removed
    else if(key == 't'){
        
        TargetPositionX = mouseX;
        TargetPositionY = mouseY;
    }
    
    //Touches
    else if(key == 'c'){
        // Normal particle
        Particle * p = particleSystem.AddParticle(new Particle(20,20, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,15), 20));
        p->SetColor(color);
        p->Setup();
        
    }
    else if(key == 'v')
    {
        // Fireball
        Particle * p = particleSystem.AddParticle(new ParticleFireball(20,20, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,150), 20));
        p->SetColor(color);
        p->Setup();
        FireballSound.play();
    }
    else if(key == 'b'){
        // Firework
        Particle * p = particleSystem.AddParticle(new ParticleFirework(20,2, Vector3D(center->x,center->y),Vector3D(mouseX - center->x, mouseY -center->y), Vector3D(0,150), 10));
        p->SetColor(color);
        p->Setup();
        p->ExplosionSound.setVolume(Volume);
        FireworkSound.play();
    }
    else if(key == 'n'){
        // Laser
        for(int i = 0; i < 100; i++)
        {
            Particle * p = particleSystem.AddParticle(new ParticleLaser(20,1, Vector3D((center->x),center->y).Add(Vector3D(mouseX - center->x, mouseY -center->y).Normalize().Multiply(i)),Vector3D(mouseX - center->x, mouseY -center->y).Multiply(5), Vector3D(0,0), 5));
            p->SetColor(color);
            p->Setup();
        }
        
        LaserSound.play();
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
