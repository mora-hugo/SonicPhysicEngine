#pragma once
#include "ofCamera.h"
#include "../Math/Vector3D.h"
class ofApp;

class FPSCamera : public ofCamera
{
public:
    FPSCamera(const ofApp * Context);

    void Update(const Vector3D& DeltaRot);

    void SetSensitivity(float Sensitivity);

    float GetSensitivity() const;

    void Setup();

    void End();

    void StartDrawing();

    void EndDrawing();

    

    
private:
    const ofApp * Context;

    float Sensitivity = 0.1f;

    
};
