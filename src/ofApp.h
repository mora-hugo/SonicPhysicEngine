#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Public/Engine/GameWorld.h"
#include "Public/Math/Vector3D.h"
#include "Public/Particle/Particle.h"
#include "Public/Particle/ParticleSystem/ParticleSystem.h"

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

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

	Vector3D GetCenter() const;
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

	
	
	double FrameTime;

	ofSoundPlayer FireballSound;
	ofSoundPlayer FireworkSound;
	ofSoundPlayer LaserSound;
	float Volume = 0.5f;

	GameWorld GameWorld;

private:
	void OnKeyPressed(const KeyboardEvent& event);
};
