//
// Created by menegais1 on 23/05/2020.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Vectors/Vector3.h"
#include "Material.h"

class Sphere {
public:
    Sphere();

    dvec3 center;
    float radius;
    Material material;

    Sphere(const dvec3 &center, float radius);

    Sphere(const dvec3 &center, float radius, Material material);
};


#endif //RAYTRACER_SPHERE_H
