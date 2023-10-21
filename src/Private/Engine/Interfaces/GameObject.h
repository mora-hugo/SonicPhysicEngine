#pragma once

class GameObject
{
public:
    virtual void Update() = 0;

    virtual void Draw() = 0;

    virtual void BeginPlay() = 0;

    virtual void EndPlay() = 0;

    
};
