#include "ofApp.h"

#include <GLFW/glfw3.h>

#include "time.h"
#include "Public/Engine/EventManager.h"
#include "Public/Engine/InputSystem.h"
#include "Public/Engine/MouseEvent.h"
#include "Public/Engine/KeyboardEvent.h"
#include "Public/Engine/GameWorld.h"
#include "ofxAssimpModelLoader.h"
#include "Public/Config/Config.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    Config::Parse();
    // the camera is reversed, so we need to invert the world
    
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
    gui.add(ProjectileVolume.setup("Projectiles Volume", ofToFloat(Config::get("VOLUME")), 0.01f, 1.0f));
    gui.add(launchBall.setup("Projectile de base | " + ofToUpper(Config::get("KEY_THROW_BASE_PARTICLE"))));
    gui.add(launchFireBall.setup("FireBall | " + ofToUpper(Config::get("KEY_THROW_FIREBALL"))));
    gui.add(launchthirdBall.setup("Firework | " + ofToUpper(Config::get("KEY_THROW_FIREWORK"))));
    gui.add(launchFourthBall.setup("Laser | " + ofToUpper(Config::get("KEY_THROW_LASER"))));
    
    bHide = false;

    // Loading sounds
    FireballSound.load("fireball_sound.wav");
    FireworkSound.load("FireworkWhistle.mp3");
    LaserSound.load("laserfire.ogg");

    yourModel.load("model.fbx", 20);
    yourModel.disableColors();
    
    GameWorld.BeginPlay(this);
    // Cachez le curseur de la souris
    ofHideCursor();

    // Déplacez la fenêtre au centre de l'écran
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, ofGetScreenHeight() / 2 - ofGetHeight() / 2);
    Camera.setPosition(1100,-700,850);

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
    EventManager::OnVolumeModified(ProjectileVolume);
    
    Config::set("VOLUME", std::to_string(ProjectileVolume));
    FireballSound.setVolume(ProjectileVolume);
    FireworkSound.setVolume(ProjectileVolume);
    LaserSound.setVolume(ProjectileVolume);
    Volume = ProjectileVolume;
}



//--------------------------------------------------------------
void ofApp::update(){
    

    // -------------
    ProcessInputs();   
    FrameTime = ofGetLastFrameTime();
    GameWorld.Update(FrameTime);
    
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(!bHide){
        gui.draw();
    }
    Camera.begin();
/*
    // draw the GUI
    ofNoFill();
    ofSetColor(color);
    ofDrawCircle(center, 35 );
   // ofDrawCircle(TargetPositionX,TargetPositionY, 30);
    ofDrawLine(center->x,center->y, (mouseX), (mouseY));
*/
    
    GameWorld.Draw();
    yourModel.drawFaces();
    Camera.end();
    
}

ofApp::~ofApp()
{
    GameWorld.EndPlay();
    Config::Save();
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
    MouseEvent event(x, y, MouseEvent::GetMouseKeyFromInt(button), MouseEventType::MOUSE_DRAGGED);
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

}