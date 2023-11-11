#include "../../Public/Controller/Player.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Engine/EventManager.h"
#include "../../Public/GameObjects/RigidBody.h"


Player::Player(ofApp * Context, const double& mass, const Vector3D& position, const Vector3D& velocity, int SphereRadius) :
    GameObject(mass, position, velocity, SphereRadius), Camera{Context}
{
}

void Player::Setup()
{
    GameObject::Setup();
    bool bIsloaded = Weapon.load("rocket_launcher_m236.glb",20);
    Weapon.setScale(0.1,0.1,0.1);

    
}

void Player::Draw()
{
    Camera.setPosition(GetPosition().Sub(CameraOffset));
    Weapon.drawFaces();
    GameObject::Draw();
}

void Player::Update(double f)
{
    GameObject::Update(f);
    const float offsetX = WeaponOffset.GetX();
    const float offsetY = WeaponOffset.GetY();
    const float offsetZ = WeaponOffset.GetZ();

    const ofVec3f cameraPosition = Camera.getPosition();
    const ofVec3f forwardVector = Camera.getLookAtDir();
    const ofVec3f rightVector = Camera.getSideDir();

    const ofVec3f positionOffset = forwardVector * offsetX + rightVector * offsetY;
    Weapon.setPosition(cameraPosition.x + positionOffset.x, cameraPosition.y + positionOffset.y, cameraPosition.z + positionOffset.z + offsetZ);

    const float rotationX = -atan2(forwardVector.y, sqrt(forwardVector.x * forwardVector.x + forwardVector.z * forwardVector.z)) * RAD_TO_DEG;
    const float rotationY = -atan2(forwardVector.x, forwardVector.z) * RAD_TO_DEG;
    

    Weapon.setRotation(0, rotationY + 180, 0, 1, 0);
    Weapon.setRotation(1, rotationX, 1, 0, 0);
    
    if(bIsGoingForward)
    {
        Vector3D ForwardVector = Camera.getLookAtDir();
        ForwardVector.SetY(0);
        AddPosition(ForwardVector.Normalize()*Speed*ofGetLastFrameTime());
    }
    

    
}

void Player::Jump()
{
    AddImpulse(Vector3D(0, -JumpForce, 0));
}

void Player::Fire(GameWorld * Context)
{
    GameObject * gameobject = Context->GetObjectsArray()->SpawnObject(new RigidBody(Vector3D(1,1,1),1, GetLaunchPoint()-GetCamera()->getLookAtDir()*10, GetCamera()->getLookAtDir()*10, 1, false));
    SetCameraTarget(gameobject);
    TPSCamera.resetTransform();
}


void Player::StartWalkingForward()
{
    bIsGoingForward = true;
}

void Player::StopWalkingForward()
{
   bIsGoingForward = false; 
}

void Player::StartPlayerSee()
{
    if(CameraTarget)
        TPSCamera.setTarget(CameraTarget->GetPosition());

    
    TPSCamera.setDistance(TPSCameraDistanceBeetweenObject);
    if(!CameraTarget && bIsUsingTPSCamera)
        std::cout << "WARNING : Camera target is null" << std::endl;
    bIsUsingTPSCamera ? TPSCamera.begin() : Camera.begin();

    if(bOpacityIsIncreasing)
        opacity++;
    else
        opacity--;
    
    if(opacity >= 255)
    {
        bOpacityIsIncreasing = false;
    }
    else if(opacity <= 0)
    {
        bOpacityIsIncreasing = true;
    }
        
    
    if(CameraTarget)
    {
        
        Vector3D Position = CameraTarget->GetPosition();

    }
}

void Player::SetCameraTarget(GameObject* Target)
{
   CameraTarget = Target;
}

void Player::ToggleCamera()
{
    bIsUsingTPSCamera = !bIsUsingTPSCamera;
}

void Player::SwitchCameraToFPS(bool bIsFPSCamera)
{
    bIsUsingTPSCamera = !bIsFPSCamera;
}

bool Player::IsUsingFPSCamera() const
{
    return !bIsUsingTPSCamera;
}

void Player::StopPlayerSee()
{
    bIsUsingTPSCamera ? TPSCamera.end() : Camera.end();
}

const FPSCamera* Player::GetCamera() const
{
    return &Camera;
}

const TPSCamera* Player::GetTPSCamera() const
{
    return &TPSCamera;
}

Vector3D Player::GetLaunchPoint()
{
    return Vector3D(Weapon.getPosition().x,Weapon.getPosition().y,Weapon.getPosition().z)+Camera.getLookAtDir()*100;
}

void Player::OnRotate(const Vector3D& DeltaRot)
{
    Camera.UpdateRotation(DeltaRot);
}
