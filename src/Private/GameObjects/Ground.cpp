#include "../../Public/GameObjects/Ground.h"

Ground::Ground() : ofPlanePrimitive(1000,1000,100,OF_PRIMITIVE_TRIANGLES)
{
    this->rotateDeg(90,1,0,0);
    this->set(10000,10000,1000,1000);
    setPosition(0,0,0);
    
    img.load("ground.jpg");
    img.getTextureReference().setTextureWrap( GL_REPEAT, GL_REPEAT );
    this->mapTexCoordsFromTexture(img.getTexture());
    
}


void Ground::Draw() const
{
    ofDisableArbTex();
    img.getTexture().bind();
    
    drawFaces();
    img.getTexture().unbind();
}

