#include "Material.h"

bool Lambertian::Scatter(const Ray& ray, const RayCastHit_t& hit, glm::vec3& attenuation, Ray& scatter) const
{
	//glm::vec3 target = (hit.point + hit.normal + randomInUnitSphere());
	glm::vec3 direction = glm::normalize((hit.normal + randomInUnitSphere()));

	scatter = { hit.point, direction };
	attenuation = albedo;
	return true;
}

bool Metal::Scatter(const Ray& ray, const RayCastHit_t& hit, glm::vec3& attenuation, Ray& scatter) const
{
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

	scatter.origin = hit.point;
	scatter.direction = reflected + (randomInUnitSphere()) * fuzz;
	attenuation = albedo;

	return glm::dot(scatter.direction, hit.normal) > 0;
}
