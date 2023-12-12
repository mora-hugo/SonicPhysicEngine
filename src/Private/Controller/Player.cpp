#include "../../Public/Controller/Player.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Engine/EventManager.h"
#include "../../Public/GameObjects/Cube.h"


Player::Player(ofApp * Context, const double& mass, const Vector3D& position, const Vector3D& velocity, int SphereRadius) :
    GameObject(mass, position, velocity, SphereRadius, false), Camera{Context}
{
    AddTag("Player");
    boxCollision.Width = 200;
    boxCollision.Height = 100;
    boxCollision.Depth = 200;
}

void Player::Setup()
{
    GameObject::Setup();
    bool bIsloaded = Weapon.load("rocket_launcher_m236.glb",20);
    Weapon.setScale(0.1,0.1,0.1);
    

    AmmoText.load("leadcoat.ttf", 30);
    AmmoTextAmount.load("leadcoat.ttf", 30);


    
}

void Player::Draw()
{
    Camera.setPosition(GetPosition().Sub(CameraOffset));
    Weapon.drawFaces();
    GameObject::Draw();
    boxCollision.Draw();

}

void Player::Update(double f)
{
    
    GameObject::Update(f);
    //TODO
    SetPosition(Vector3D(GetPosition().X, 0, GetPosition().Z));

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

    /*
    boxCollision.ForwardVector = Camera.getLookAtDir();
    boxCollision.RightVector = Camera.getSideDir();
    boxCollision.UpVector = Camera.getUpDir();
    
    Quaternion RotationQuat(Camera.getOrientationQuat().w, Camera.getOrientationQuat().x, Camera.getOrientationQuat().y, Camera.getOrientationQuat().z);


    boxCollision.rotation =  RotationQuat;
    */
    if(bIsGoingForward)
    {
        Vector3D ForwardVector = Camera.getLookAtDir();
        ForwardVector.SetY(0);
        AddPosition(ForwardVector.Normalize()*Speed*ofGetLastFrameTime());
    }

    if(bISGoingBackward)
    {
        Vector3D ForwardVector = -Camera.getLookAtDir();
        ForwardVector.SetY(0);
        AddPosition(ForwardVector.Normalize()*Speed*ofGetLastFrameTime());
    }

    if(bIsStrafingLeft)
    {
        Vector3D RightVector = -Camera.getSideDir();
        RightVector.SetY(0);
        AddPosition(RightVector.Normalize()*Speed*ofGetLastFrameTime());
    }

    if(bIsStrafingRight)
    {
        Vector3D RightVector = Camera.getSideDir();
        RightVector.SetY(0);
        AddPosition(RightVector.Normalize()*Speed*ofGetLastFrameTime());
    }
    

    
}

void Player::Jump()
{
    //Not implemented this phase
}

void Player::Reload()
{
    ammo = MaxAmmo;
}

void Player::Fire(GameWorld * Context)
{
    //Call when the player fire
    if(ammo <= 0) return;
    
    GameObject * gameobject = Context->GetObjectsArray()->SpawnObject(new Cube(20,ofColor::red,5, (GetLaunchPoint()-GetCamera()->getLookAtDir()*10), Vector3D((GetCamera()->getLookAtDir()*1000))+GetVelocity(), 200, true));

    SetCameraTarget(gameobject);
    gameobject->AddForce(Force(Vector3D(0,0,0), 1, Constant));
    Force force = Force((-GetCamera()->getLookAtDir()*10), 1, Constant, Vector3D(0,1,0));
    gameobject->AddForce(force);
    TPSCamera.resetTransform();
    ammo--;
}


void Player::StartWalkingForward()
{
    bIsGoingForward = true;
}

void Player::StopWalkingForward()
{
   bIsGoingForward = false; 
}

void Player::StartWalkingBackward()
{
    bISGoingBackward = true;
}

void Player::StopWalkingBackward()
{
    bISGoingBackward = false;
}

void Player::StartStrafingLeft()
{
    bIsStrafingLeft = true;
}

void Player::StopStrafingLeft()
{
    bIsStrafingLeft = false;
}

void Player::StartStrafingRight()
{
    bIsStrafingRight = true;
}

void Player::StopStrafingRight()
{
    bIsStrafingRight = false;
}

void Player::StartPlayerSee()
{
    /* Before Camera Rendering */
    if(CameraTarget)
        TPSCamera.setTarget(CameraTarget->GetPosition());

    //Draw bigger string
    AmmoText.drawString("Ammo",60, ofGetWindowSize().y - 60);
    const std::string ammotext = std::to_string(ammo) + " / " + std::to_string(MaxAmmo);
    AmmoTextAmount.drawString(ammotext,60, ofGetWindowSize().y - 30);

    


    
    TPSCamera.setDistance(TPSCameraDistanceBeetweenObject);
    if(!CameraTarget && bIsUsingTPSCamera)
        std::cout << "WARNING : Camera target is null" << std::endl;

    /* Before Camera Rendering End */
    bIsUsingTPSCamera ? TPSCamera.begin() : Camera.begin();
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
