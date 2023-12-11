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
        ofDrawSphere(vertices[i], 20);
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

bool Box::IsCollidingWithRectangle(Box& p2, CollisionData& data1)
{
    /*if(collision && abs(data1.PenetrationDepth) < abs(interpenetration))
    {
        data1.PenetrationDepth = abs(interpenetration);
        data1.CollisionNormal = plane.Normal;
        data1.CollisionPoint = vertex - plane.Normal.Multiply(plane.Normal.DotProduct(vertex - plane.Point));
    }*/
    std::vector<CollisionData> collisions;
    
    auto vertices_A = GetVertices();
    auto planes_B = p2.GetPlanes();

    for(const Vector3D& vertex : vertices_A)
    {
        bool collision = true;
        for(const Plane& plane : planes_B)
        {
            const double interpenetration = plane.Normal.DotProduct(vertex - plane.Point);
            collision = collision && interpenetration <= 0;
        }
        if(collision)
        {
            CollisionData data = CollisionData();
            
            collisions.push_back(CollisionData());
        }
    }
    return collisions.size()>0;
}

Box Box::InitBox()
{
    return Box(200, 200, 200);
}
