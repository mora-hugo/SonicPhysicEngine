#include "../../Public/GameObjects/Box.h"
#include "../../Public/Math/Matrix3.h"

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
    PrimBox.setGlobalOrientation(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
    PrimBox.drawWireframe();
    std::vector<ofColor> planeColors = {ofColor::red, ofColor::green, ofColor::blue, ofColor::yellow, ofColor::cyan, ofColor::magenta};
    std::vector<Plane> planes = GetPlanes();
    for (size_t i = 0; i < planes.size(); ++i)
    {
        ofSetColor(planeColors[i]);
        ofDrawLine(planes[i].Point, planes[i].Point + planes[i].Normal * 100);
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

bool Box::IsCollidingWithRectangle(Box& p2)
{
    // Box 1
    std::vector<Plane> box_planes_A = GetPlanes();

    // Box 2
    std::vector<Vector3D> box_vertices_B = p2.GetVertices();

    for (const Plane& plane : box_planes_A)
    {
        bool allVerticesOnSameSide = true;

        for (const Vector3D& vertex : box_vertices_B)
        {
            const double interpenetration = plane.Normal.DotProduct(vertex - plane.Point);
            if (interpenetration < 0)
            {
                allVerticesOnSameSide = false;
                break;
            }
        }

        if (allVerticesOnSameSide)
        {
            return false;
        }
    }

    std::vector<Plane> box_planes_B = p2.GetPlanes();

    for (const Plane& plane : box_planes_B)
    {
        bool allVerticesOnSameSide = true;

        for (const Vector3D& vertex : GetVertices())
        {
            const double interpenetration = plane.Normal.DotProduct(vertex - plane.Point);
            if (interpenetration < 0)
            {
                allVerticesOnSameSide = false;
                break;
            }
        }

        if (allVerticesOnSameSide)
        {
            return false;
        }
    }

    return true;
}


Box Box::InitBox()
{
    return Box(200, 200, 200);
}
