#include "../../Public/Math/Spring.h"

Spring::Spring(GameObject* p1, GameObject* p2, double springConstant, double restLength, double damping) : firstGameObject(p1), secondGameObject(p2), springConstant(springConstant), restLength(restLength), damping(damping)
{
}
