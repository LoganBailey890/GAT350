#include "Material.h"

bool Lambertian::Scatter(const Ray& ray, const RayCastHit_t& hit, glm::vec3& attenuation, Ray& scatter) const
{
	//glm::vec3 target = (hit.point + hit.normal + randomInUnitSphere());
	glm::vec3 direction = glm::normalize((hit.normal + randomInUnitSphere()));

	scatter = { hit.point, direction };
    attenuation = albedo->value(hit.uv, hit.point);	
    return true;
}

bool Metal::Scatter(const Ray& ray, const RayCastHit_t& hit, glm::vec3& attenuation, Ray& scatter) const
{
	glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

	scatter.origin = hit.point;
	scatter.direction = reflected + (randomInUnitSphere()) * fuzz;
    attenuation = albedo->value(hit.uv, hit.point);
	return glm::dot(scatter.direction, hit.normal) > 0;
}
bool Dielectric::Scatter(const Ray& ray, const RayCastHit_t& hit, glm::vec3& attenuation, Ray& scattered) const
{
    attenuation = albedo->value(hit.uv, hit.point);
    glm::vec3 refracted;
    glm::vec3 normal;
    float cosine;
    float refractionRatio;

    // check if ray is hitting the inside of the surface or from the outside, adjust values
    if (glm::dot(ray.direction, hit.normal) > 0)
    {
        // ray hits inside of surface
        normal = -hit.normal;
        refractionRatio = refractionIndex;
        cosine = refractionIndex * glm::dot(ray.direction, hit.normal) / ray.direction.length();
    }
    else
    {
        // ray hits outside of surface
        normal = hit.normal;
        refractionRatio = 1.0f / refractionIndex;
        cosine = -glm::dot(ray.direction, hit.normal) / ray.direction.length();
    }

    float reflectProbability = 1.0f;
    if (refract(ray.direction, normal, refractionRatio, refracted))
    {
        reflectProbability = schlick(cosine, refractionIndex);
    }

    glm::vec3 reflected = reflect(glm::normalize(ray.direction), hit.normal);

    scattered = (random01() < reflectProbability) ? Ray{ hit.point, reflected } : Ray{ hit.point, refracted };

    return true;
}

