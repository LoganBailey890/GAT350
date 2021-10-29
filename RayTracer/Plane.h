#pragma once
#include "Geometry.h"

class Plane : public Geometry
{
public:
	Plane() = default;
	Plane(const glm::vec3& center, const glm::vec3& normal):
		center{center},
		normal{normal}
	{
	}
	bool Hit(const Ray& ray, float tMin, float tMax, RayCastHit_t& hit) override;


public:
	glm::vec3 center{ 0,0,0 };
	glm::vec3 normal{ 0,0,0 };

};