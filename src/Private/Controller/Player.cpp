#include "../../Public/Controller/Player.h"
#include "../../Public/Particle/ParticleFireball.h"
#include "../../ofApp.h"
#include "../../Public/Engine/EventManager.h"


Player::Player(ofApp * Context, const double& mass, const Vector3D& position, const Vector3D& velocity, int SphereRadius) :
    GameObject(mass, position, velocity, SphereRadius), Camera{Context}
{
}

void Player::Setup()
{
    GameObject::Setup();
    bool bIsloaded = Weapon.load("rocket_launcher_m236.glb",20);
    Weapon.setScale(0.1,0.1,0.1);
    ofMouseEventArgs m(ofMouseEventArgs::Pressed, ofGetWidth()/2.0f, ofGetHeight()/2.0f, OF_MOUSE_BUTTON_LEFT);

    EventManager::KeyboardEvent.subscribe([=](const KeyboardEvent& event) {
        if(bIsUsingTPSCamera && event.InputType == KeyboardEventType::KEY_PRESSED && (event.key == Config::getChar("KEY_QUIT_TPS") || event.key == 'F')) 
        {
            SwitchCameraToFPS(true);
        }
    });
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
    
    GameObject * gameobject = Context->GetObjectsArray()->SpawnObject(new ParticleFireball(50,1, GetLaunchPoint(), GetCamera()->getLookAtDir()*50, Vector3D::Zero(),5));
    SetCameraTarget(gameobject);
    SwitchCameraToFPS(false);
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

        ofDrawBitmapStringHighlight("Switch Camera to the fired object using " + std::string(1,Config::getChar("KEY_QUIT_TPS")) + " or F", 100, 100, ofColor(255, 255, 255, opacity), ofColor(0, 0, 0, opacity));
    }
}

void Player::SetCameraTarget(GameObject* Target)
{
   CameraTarget = Target;
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
