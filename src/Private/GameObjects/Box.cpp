#include "../../Public/GameObjects/Box.h"

#include "of3dGraphics.h"

Box::Box()
{
    Width = 200;
    Height = 200;
    Depth = 200;
}
void Box::SetColor(ofColor color2)
{
    this->color = color2;
}
Box::Box(float width, float height, float depth)
{
    Width = width;
    Height = height;
    Depth = depth;
}

void Box::Draw()
{
    ofSetColor(color);
    ofNoFill();
    ofBoxPrimitive PrimBox = ofBoxPrimitive(Width, Height, Depth);
    PrimBox.setPosition(position);
    //PrimBox.setGlobalOrientation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
    PrimBox.drawWireframe();
    ofFill();
    ofSetColor(ofColor::white);
}

void Box::Update(double f)
{
    
    
}

bool Box::IsCollidingWithRectangle(Box& p2)
{
    // Vecteurs représentant les axes de chaque boîte
    Vector3D axes[15] = {
        ForwardVector,
        UpVector,
        RightVector,
        p2.ForwardVector,
        p2.UpVector,
        p2.RightVector,
        ForwardVector.CrossProduct(p2.ForwardVector),
        ForwardVector.CrossProduct(p2.UpVector),
        ForwardVector.CrossProduct(p2.RightVector),
        UpVector.CrossProduct(p2.ForwardVector),
        UpVector.CrossProduct(p2.UpVector),
        UpVector.CrossProduct(p2.RightVector),
        RightVector.CrossProduct(p2.ForwardVector),
        RightVector.CrossProduct(p2.UpVector),
        RightVector.CrossProduct(p2.RightVector)
    };

    for (int i = 0; i < 15; ++i)
    {
        // Projetter les boîtes sur l'axe
        double projection1 = position.DotProduct(axes[i]);
        double projection2 = p2.position.DotProduct(axes[i]);

        // Calculer la distance entre les projections
        double distance = std::abs(projection1 - projection2);

        // Calculer la somme des demi-largeurs le long de l'axe
        double sumHalfWidths = (Width / 2) + (p2.Width / 2);

        // Vérifier la séparation le long de l'axe
        if (distance > sumHalfWidths)
        {
            // Les boîtes sont séparées le long de cet axe, donc pas de collision
            return false;
        }
    }

    // Aucune séparation le long de tous les axes, donc collision
    return true;
}


Box Box::InitBox()
{
    return Box(200, 200, 200);
}
