#pragma once
#include "Types.h"

struct RayCastHit_t
{
	float t{ 0 };
	glm::vec3 point;
	glm::vec3 normal;
};
struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() = default;
	Ray(const glm::vec3& origin, const glm::vec3& direction) : origin{ origin }, direction{ direction }{}

	glm::vec3 pointAt(float t) const { return origin + (direction * t); }

};