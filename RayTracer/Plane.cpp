#include "Plane.h"

bool Plane::Hit(const Ray& ray, float tMin, float tMax, RayCastHit_t& hit)
{
	float denominator = glm::dot(ray.direction, normal);

	if (abs(denominator) < glm::epsilon<float>())
	{
		return false;
	}

	float t = glm::dot(center - ray.origin, normal) / denominator;

	if (t < 0)
	{
		return false;
	}

	if (t >= tMin && t <= tMax)
	{
		hit.t = t;
		hit.point = ray.pointAt(t);
		hit.normal = normal;
		hit.material = material.get();
		
		return true;
	}
}
