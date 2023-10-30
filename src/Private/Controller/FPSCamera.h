#pragma once
#include "ofCamera.h"

class ofApp;

class FPSCamera : protected ofCamera
{
public:
    FPSCamera(ofApp * Context);

    void Update();

    void Setup();

    void End();

    void StartDrawing();

    void EndDrawing();

    

    
private:
    ofApp * Context;

    
};
