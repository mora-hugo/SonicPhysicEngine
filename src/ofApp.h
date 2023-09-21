#pragma once

#include "ofMain.h"
#include "ofxGui.h"
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
	void ringButtonPressed();
	void FireballVolumeChanged(float & fireballVolume);

	bool bHide;

	ofxFloatSlider radius;
	ofxColorSlider color;
	ofxVec2Slider center;
	ofxIntSlider circleResolution;
	ofxToggle filled;
	ofxButton twoCircles;
	ofxButton ringButton;
	ofxLabel screenSize;
	ofxButton launchFireBall;
	ofxFloatSlider fireballVolume;
	ofxButton launchFromBall;

	ofxPanel gui;

	ofSoundPlayer ring;

	ParticleSystem particleSystem;
	
	double FrameTime;

	ofSoundPlayer FireballSound;
	
};
