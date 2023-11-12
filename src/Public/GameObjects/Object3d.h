#pragma once

#include "GameObject.h"
#include "ofxAssimpModelLoader.h"

class Object3d : public GameObject
{
public:
    Object3d(const std::string &filepath, const Vector3D& position = Vector3D::Zero(), const Vector3D& rotation = Vector3D::Zero(), const Vector3D& scale = Vector3D(1,1,1), const Vector3D& CollisionRectangle = Vector3D(1,1,1));

public:
    void Setup() override;
    void Draw() override;
    void Update(double f) override;
private:
    ofxAssimpModelLoader modelLoaded;
    Vector3D CollisionRectangle;
    
};
