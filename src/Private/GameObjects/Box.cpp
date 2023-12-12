#include "../../Public/GameObjects/Box.h"

#include <valarray>

#include "../../Public/Math/Matrix3.h"

#include "of3dGraphics.h"
#include "../../Public/GameObjects/Structs/CollisionData.h"

Box::Box()
{
    Width = 200;
    Height = 200;
    Depth = 200;
    ForwardVector = rotation.RotateVector(Vector3D::Forward());
    UpVector = rotation.RotateVector(Vector3D::Up());
    RightVector = rotation.RotateVector(Vector3D::Right());
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
    
    ofBoxPrimitive PrimBox = ofBoxPrimitive(Width, Height, Depth);
    PrimBox.setPosition(position);
    PrimBox.setGlobalOrientation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
    PrimBox.drawWireframe();
    std::vector<ofColor> planeColors = {ofColor::red, ofColor::green, ofColor::blue, ofColor::yellow, ofColor::cyan, ofColor::magenta};
    std::vector<Plane> planes = GetPlanes();
    for (size_t i = 0; i < planes.size(); ++i)
    {
        ofSetColor(planeColors[i]);
        ofDrawLine(planes[i].Point, planes[i].Point + planes[i].Normal * 100);
    }
    std::vector<Vector3D> vertices = GetVertices();
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        ofSetColor(ofColor::orange);
        ofDrawSphere(vertices[i], 5);
    }
    // Draw the axes
   
    
    ofFill();
    ofSetColor(ofColor::white);
}
std::vector<Vector3D> Box::GetVertices() const
{
    // Calculer les demi-dimensions
    double halfWidth = Width / 2.0;
    double halfHeight = Height / 2.0;
    double halfDepth = Depth / 2.0;

    // Rotation de la boîte
    Matrix3 rotationMatrix = Matrix3().CreateRotationMatrix(rotation);

    // Calculer les sommets non transformés de la boîte
    std::vector<Vector3D> vertices;
    vertices.push_back(Vector3D(-halfWidth, -halfHeight, -halfDepth));
    vertices.push_back(Vector3D(halfWidth, -halfHeight, -halfDepth));
    vertices.push_back(Vector3D(halfWidth, halfHeight, -halfDepth));
    vertices.push_back(Vector3D(-halfWidth, halfHeight, -halfDepth));
    vertices.push_back(Vector3D(-halfWidth, -halfHeight, halfDepth));
    vertices.push_back(Vector3D(halfWidth, -halfHeight, halfDepth));
    vertices.push_back(Vector3D(halfWidth, halfHeight, halfDepth));
    vertices.push_back(Vector3D(-halfWidth, halfHeight, halfDepth));

    // Appliquer la position et la rotation à chaque sommet
    for (Vector3D& vertex : vertices)
    {
        vertex = position + rotationMatrix * vertex;
    }

    return vertices;
}

std::vector<Plane> Box::GetPlanes() const
{
    const Vector3D upNormal = UpVector;
    const Vector3D frontNormal = ForwardVector;
    const Vector3D backNormal = ForwardVector.Negate();
    const Vector3D leftNormal = RightVector.Negate();
    const Vector3D rightNormal = RightVector;
    const Vector3D downNormal = UpVector.Negate();

    const Vector3D upPoint =  position + upNormal * (Height / 2.0);
    const Vector3D frontPoint = position + frontNormal * (Depth / 2.0);
    const Vector3D backPoint = position + backNormal * (Depth / 2.0);
    const Vector3D leftPoint = position + leftNormal * (Width / 2.0);
    const Vector3D rightPoint = position + rightNormal * (Width / 2.0);
    const Vector3D downPoint = position + downNormal * (Height / 2.0);

    std::vector<Plane> planes;
    planes.push_back(Plane(upNormal, upPoint));
    planes.push_back(Plane(frontNormal, frontPoint));
    planes.push_back(Plane(backNormal, backPoint));
    planes.push_back(Plane(leftNormal, leftPoint));
    planes.push_back(Plane(rightNormal, rightPoint));
    planes.push_back(Plane(downNormal, downPoint));
    return planes;
    

}

void Box::Update(double f)
{
    
    
}
void Box::GetCollisionAtFace(Box &p2, int faceIndex, CollisionData &OutCollisionData)
{
    auto vertices_A = GetVertices();
    for(const Vector3D& vertex : vertices_A)
    {
        if(faceIndex == 1)
        {
            const Plane plane_forward = GetPlanes()[1];
            const Plane plane_backward = GetPlanes()[2];

            const double interpenetration_forward = plane_forward.Normal.DotProduct(vertex - plane_forward.Point);
            const double interpenetration_backward = plane_backward.Normal.DotProduct(vertex - plane_backward.Point);
            if(interpenetration_forward > 0 || interpenetration_backward > 0) continue;
            if(abs(interpenetration_forward) < abs(interpenetration_backward))
            {
                if(abs(interpenetration_forward) > OutCollisionData.PenetrationDepth) continue;
                OutCollisionData.CollisionNormal = plane_forward.Normal;
                OutCollisionData.PenetrationDepth = abs(interpenetration_forward);
                OutCollisionData.CollisionPoint = vertex.Sub(plane_forward.Normal.Multiply(plane_forward.Normal.DotProduct((vertex.Sub(plane_forward.Point)))));
            }
            else
            {
                if(abs(interpenetration_backward) > OutCollisionData.PenetrationDepth) continue;
                OutCollisionData.CollisionNormal = plane_backward.Normal;
                OutCollisionData.PenetrationDepth = abs(interpenetration_backward);
                OutCollisionData.CollisionPoint = vertex.Sub(plane_backward.Normal.Multiply(plane_backward.Normal.DotProduct((vertex.Sub(plane_backward.Point)))));
            }
        }
        else if(faceIndex == 2)
        {
            const Plane plane_up = GetPlanes()[0];
            const Plane plane_down = GetPlanes()[5];

            const double interpenetration_up = plane_up.Normal.DotProduct(vertex - plane_up.Point);
            const double interpenetration_down = plane_down.Normal.DotProduct(vertex - plane_down.Point);
            if(interpenetration_up > 0 || interpenetration_down > 0) continue;

            if(abs(interpenetration_up) < abs(interpenetration_down))
            {
                if(abs(interpenetration_up) > OutCollisionData.PenetrationDepth) continue;
                OutCollisionData.CollisionNormal = plane_up.Normal;
                OutCollisionData.PenetrationDepth = abs(interpenetration_up);
                OutCollisionData.CollisionPoint = vertex.Sub(plane_up.Normal.Multiply(plane_up.Normal.DotProduct((vertex.Sub(plane_up.Point)))));
            }
            else
            {
                if(abs(interpenetration_down) > OutCollisionData.PenetrationDepth) continue;
                OutCollisionData.CollisionNormal = plane_down.Normal;
                OutCollisionData.PenetrationDepth = abs(interpenetration_down);
                OutCollisionData.CollisionPoint = vertex.Sub(plane_down.Normal.Multiply(plane_down.Normal.DotProduct((vertex.Sub(plane_down.Point)))));
            }
        }
        else if(faceIndex == 3)
        {
            const Plane plane_right = GetPlanes()[4];
            const Plane plane_left = GetPlanes()[3];

            const double interpenetration_right = plane_right.Normal.DotProduct(vertex - plane_right.Point);
            const double interpenetration_left = plane_left.Normal.DotProduct(vertex - plane_left.Point);
            if(interpenetration_right > 0 || interpenetration_left > 0) continue;

            if(abs(interpenetration_right) < abs(interpenetration_left))
            {
                if(abs(interpenetration_right) > OutCollisionData.PenetrationDepth) continue;
                OutCollisionData.CollisionNormal = plane_right.Normal;
                OutCollisionData.PenetrationDepth = abs(interpenetration_right);
                OutCollisionData.CollisionPoint = vertex.Sub(plane_right.Normal.Multiply(plane_right.Normal.DotProduct((vertex.Sub(plane_right.Point)))));
            }
            else
            {
                if(abs(interpenetration_left) > OutCollisionData.PenetrationDepth) continue;
                OutCollisionData.CollisionNormal = plane_left.Normal;
                OutCollisionData.PenetrationDepth = abs(interpenetration_left);
                OutCollisionData.CollisionPoint = vertex.Sub(plane_left.Normal.Multiply(plane_left.Normal.DotProduct((vertex.Sub(plane_left.Point)))));
            }
        }
    }
}
void Box::ResolveCollision(Box &p2, CollisionType CollisionType, class CollisionData &OutCollisionData)
{
    auto vertices_A = GetVertices();
    
    auto planes_B = p2.GetPlanes();
    if(CollisionType == CollisionType::FACE)
    {
        for(const Vector3D& vertex : vertices_A)
        {
            bool collision = true;
            for(const Plane& plane : planes_B)
            {
                const double interpenetration = plane.Normal.DotProduct(vertex - plane.Point);
                collision = collision && interpenetration <= 0;
            }

        }
    }
}
bool Box::IsCollidingWithRectangle(Box& p2, CollisionData& CollisionStruct)
{
    bool res = false;
    
    auto vertices_A = GetVertices();
    auto planes_B = p2.GetPlanes();


    for(const Vector3D& vertex : vertices_A)
    {
        bool collision = true;
        
        for(const Plane& plane : planes_B)
        {
            const double interpenetration = plane.Normal.DotProduct(vertex.Sub(plane.Point));
            collision = collision && interpenetration <= 0;
            if(collision)
            {
                if(abs(interpenetration) < CollisionStruct.PenetrationDepth)
                {
                    CollisionStruct.PenetrationDepth = abs(interpenetration);
                    CollisionStruct.CollisionNormal = plane.Normal;
                    CollisionStruct.CollisionPoint = vertex.Sub(plane.Normal.Multiply(plane.Normal.DotProduct((vertex.Sub(plane.Point)))));
                }
            }
        }
        if(collision)
        {
            res = true;
        }
    }


    return res;
}

Box Box::InitBox()
{
    return Box(200, 200, 200);
}
