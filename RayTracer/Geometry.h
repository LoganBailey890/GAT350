#pragma once
#include "Types.h"
#include "Ray.h"



class Geometry
{
public:
    Geometry() = default;
    virtual ~Geometry() = default;



    virtual bool Hit(const Ray& r, float tMin, float tMax, RayCastHit_t& hit) = 0;
};