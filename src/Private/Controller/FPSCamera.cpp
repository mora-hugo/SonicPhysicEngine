#include "../../Public/Controller/FPSCamera.h"

#include "ofAppRunner.h"

FPSCamera::FPSCamera(const ofApp * Context) : ofCamera(), Context(Context)
{
    this->setScale(1, -1, 1);
    
}

void FPSCamera::Update(const Vector3D& DeltaRot)
{
    float deltaX = DeltaRot.GetX();
    float deltaY = DeltaRot.GetY();

    
    this->rotateDeg(-deltaX * Sensitivity, ofVec3f(0, 1, 0)); 
    this->tiltDeg(deltaY * Sensitivity);
    SetCursorPos(ofGetWindowPositionX()+ofGetWidth()/2,ofGetWindowPositionY()+ofGetHeight()/2);
 
}

void FPSCamera::SetSensitivity(float Sensitivity)
{
    this->Sensitivity = Sensitivity;
}

float FPSCamera::GetSensitivity() const
{
    return this->Sensitivity;

}

void FPSCamera::Setup()
{
}

void FPSCamera::End()
{
}

void FPSCamera::StartDrawing()
{
}

void FPSCamera::EndDrawing()
{
}

