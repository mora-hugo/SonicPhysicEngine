#pragma once

#include "Public/Controller/FPSCamera.h"
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "Public/Engine/GameWorld.h"
#include "Public/GameObjects/Ground.h"
#include "Public/Math/Vector3D.h"
#include "Public/Particle/Particle.h"
#include "Public/Particle/ParticleSystem/ParticleSystem.h"

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
	~ofApp();

	// an exit for the listener
	void exit();

	void ProcessInputs();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	
	void circleResolutionChanged(int & circleResolution);
	void ProjectileVolumeChanged(float & ProjectileVolume);

	
	bool bHide;

	

	ofxColorSlider color;
	ofxVec2Slider center;

	ofxButton twoCircles;
	ofxButton ringButton;
	ofxLabel screenSize;
	ofxFloatSlider ProjectileVolume;
	ofxButton launchBall;
	ofxButton launchFireBall;
	ofxButton launchthirdBall;
	ofxButton launchFourthBall;

	ofxPanel gui;

	float TargetPositionX;
	float TargetPositionY;

	ofxAssimpModelLoader yourModel;
	
	double FrameTime;

	ofSoundPlayer FireballSound;
	ofSoundPlayer FireworkSound;
	ofSoundPlayer LaserSound;
	float Volume = 0.5f;

	GameWorld GameWorld;
	Vector3D lastMousePosition;

private:
	void OnKeyPressed(const KeyboardEvent& event);
};
