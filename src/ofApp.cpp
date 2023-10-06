#include "ofApp.h"
#include "time.h"
#include "Public/Engine/EventManager.h"
#include "Public/Engine/InputSystem.h"
#include "Public/Engine/MouseEvent.h"
#include "Public/Engine/KeyboardEvent.h"
#include "Public/Engine/GameWorld.h"
#include "Public/Particle/ParticleFireball.h"
#include "Public/Particle/ParticleFirework.h"
#include "Public/Particle/ParticleLaser.h"
#include "Public/Config/Config.h"

//--------------------------------------------------------------
void ofApp::setup(){

    Config::Parse();
    // Subscribe to events
    EventManager::KeyboardEvent.subscribe([=](const KeyboardEvent& event) {
        OnKeyPressed(event);
    });

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

    GameWorld.BeginPlay(this);
    
}

//--------------------------------------------------------------
void ofApp::exit(){
}

void ofApp::ProcessInputs()
{
    // call the event for each type of inputs
    EventVariant event;
    while (InputManager::getNextEvent(event))
    {
        if (std::holds_alternative<KeyboardEvent>(event)) {
            EventManager::KeyboardEvent(std::get<KeyboardEvent>(event));
        } else if (std::holds_alternative<MouseEvent>(event)) {
            EventManager::MouseEvent(std::get<MouseEvent>(event));
        }
    }
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

Vector3D ofApp::GetCenter() const
{
    
    return Vector3D(center.getPosition());
}



//--------------------------------------------------------------
void ofApp::update(){
    ProcessInputs();   
    FrameTime = ofGetLastFrameTime();
    GameWorld.Update(FrameTime);
}

//--------------------------------------------------------------
void ofApp::draw(){
   

    // draw the GUI
    ofNoFill();
    ofSetColor(color);
    ofDrawCircle(center, 35 );
   // ofDrawCircle(TargetPositionX,TargetPositionY, 30);
    ofDrawLine(center->x,center->y, (mouseX), (mouseY));
    if(!bHide){
        gui.draw();
    }
    GameWorld.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    KeyboardEvent event(key, KeyboardEventType::KEY_PRESSED);
    InputManager::addInput(event);
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    KeyboardEvent event(key, KeyboardEventType::KEY_RELEASED);
    InputManager::addInput(event);
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    MouseEvent event(x, y, MouseKey::NONE, MouseEventType::MOUSE_MOVE);
    InputManager::addInput(event);
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    MouseEvent event(x, y, MouseEvent::GetMouseKeyFromInt(button), MouseEventType::MOUSE_MOVE);
    InputManager::addInput(event);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    MouseEvent event(x, y, MouseEvent::GetMouseKeyFromInt(button), MouseEventType::MOUSE_PRESSED);
    InputManager::addInput(event);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    MouseEvent event(x, y, MouseEvent::GetMouseKeyFromInt(button), MouseEventType::MOUSE_RELEASED);
    InputManager::addInput(event);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    MouseEvent event(x, y, MouseKey::NONE, MouseEventType::MOUSE_ENTERED);
    InputManager::addInput(event);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    MouseEvent event(x, y, MouseKey::NONE, MouseEventType::MOUSE_EXITED);
    InputManager::addInput(event);
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



void ofApp::OnKeyPressed(const KeyboardEvent& event)
{
    
    //sauvegarde
    if(event.key == 'h'){
        bHide = !bHide;
    }
    else if(event.key == 'o'){
        gui.saveToFile("settings.xml");
    }
    else if(event.key == 'p'){
        gui.loadFromFile("settings.xml");
    }

    //viseur - Removed
    else if(event.key == 't'){
        
        TargetPositionX = mouseX;
        TargetPositionY = mouseY;
    }
    //Deplacement
    else if(event.key == 'w' || event.key == 'z'){
        center.setup("center", {center->x, center->y-5}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    else if(event.key == 'a' || event.key == 'q')
    {
        center.setup("center", {center->x-5, center->y}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    else if(event.key == 's'){
        center.setup("center", {center->x, center->y+5}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    else if(event.key == 'd')
    {
        center.setup("center", {center->x+5, center->y}, {0, 0}, {ofGetWidth(), ofGetHeight()});
    }
    
    //defaut
    else if(event.key == ' '){
        color = ofColor(255);
    }
    
}