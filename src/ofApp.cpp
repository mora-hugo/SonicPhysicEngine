#include "ofApp.h"

#include <GLFW/glfw3.h>

#include "Matrix3.h"
#include "Matrix4.h"
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
    
    //======[Test Matrice]======
    Matrix3 m3 = Matrix3(1,1,5
                        ,4,2,1
                        ,2,1,3);

    Matrix4 m4 = Matrix4(1,3,1,2
                        ,4,1,1,5
                        ,2,1,3,1
                        ,1,4,1,1);
    double k = 2;

    Matrix3 resAdd3 = m3 + m3; // 2 2 10 | 8 4 2 | 4 2 6
    Matrix3 resSub3 = m3 - m3;  //Matrice de 0
    Matrix3 resMultiK3 = m3 * k; // 2 2 10 | 8 4 2 | 4 2 6
    Matrix3 resMultiM3 = m3 * resAdd3; // 30 16 42 | 28 18 50 |24 14 40
    std::cout << "========[MATRIX 3 | ADD SUB MULTIPLY]========" << endl <<  std::string(resAdd3) << endl << std::string(resSub3) << endl << std::string(resMultiK3) << endl << std::string(resMultiM3) << endl ;

    m3.SetMatrix3Element(1,2, 7);
    double x3 = m3.GetMatrix3Element(1,2);
    std::cout << "========[MATRIX 3 | GET SET]========" << endl << std::string(m3) << endl << x3 << endl;    
    
    Matrix4 resAdd4 = m4 + m4; // 2 6 2 4 | 8 2 2 10 | 4 2 6 2 | 2 8 2 2
    Matrix4 resSub4 = m4 - m4; //Matrice de 0
    Matrix4 resMultiK4 = m4 * k; // 2 6 2 4 | 8 2 2 10 | 4 2 6 2 | 2 8 2 2
    Matrix4 resMultiM4 = m4 * resAdd4; // 34 30 18 40 | 30 68 26 38 | 26 28 26 26 | 40 24 18 48
    std::cout << "========[MATRIX 4 | ADD SUB MULTIPLY]========" << endl << std::string(resAdd4) << endl << std::string(resSub4) << endl << std::string(resMultiK4) << endl << std::string(resMultiM4) ;
    
    m4.SetMatrix4Element(2,3, 7);
    double x4 = m4.GetMatrix4Element(2,3);
    std::cout << "========[MATRIX 4 | GET SET]========" << endl << std::string(m4) << endl << x4 << endl;
    //======[FIN Test Matrice]======
    
    Config::Parse();
    cam.setScale(1, -1, 1);
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
    lastMouse.set(ofGetMouseX(), ofGetMouseY());
    GameWorld.BeginPlay(this);
    cam.lookAt(yourModel.getPosition());
    // Cachez le curseur de la souris
   ofHideCursor();

    // Déplacez la fenêtre au centre de l'écran
    ofSetWindowPosition(ofGetScreenWidth() / 2 - ofGetWidth() / 2, ofGetScreenHeight() / 2 - ofGetHeight() / 2);
    
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
    cam.begin();
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
    cam.end();
}

ofApp::~ofApp()
{
    GameWorld.EndPlay();
    cam.end();
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
    // Obtenez la différence de position de la souris depuis la dernière frame
    int MouseXPos = event.x;
    int MouseYPos = event.y;
    int deltaX = MouseXPos - lastMouse.x;
    int deltaY = MouseYPos - lastMouse.y;

    

    // Définissez la sensibilité de la souris
    float sensitivity = 0.1;
   

    // Appliquez la rotation de la caméra en fonction des mouvements de la souris
    cam.rotateDeg(-deltaX * sensitivity, ofVec3f(0, 1, 0)); // Utilisation de -deltaX pour inverser l'axe X
    cam.tiltDeg(deltaY * sensitivity);

    // Mettez à jour la dernière position de la souris
    
    
    SetCursorPos(ofGetWindowPositionX()+ofGetWidth()/2,ofGetWindowPositionY()+ofGetHeight()/2);
    lastMouse.set(ofGetWidth()/2,ofGetHeight()/2);

    

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
    {
        /*
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
        */
    }
}