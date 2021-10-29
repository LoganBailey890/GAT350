#pragma once
#include "Types.h"
#include "Ray.h"
#include "Material.h"



class Geometry
{
public:
    Geometry() = default;
    Geometry(std::shared_ptr<Material> material):material{material}{}

    virtual ~Geometry() = default;
    
    virtual bool Hit(const Ray& r, float tMin, float tMax, RayCastHit_t& hit) = 0;

protected:
    std::shared_ptr<Material> material;



};