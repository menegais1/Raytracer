//
// Created by menegais1 on 23/05/2020.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Vectors/Vector3.h"

class Sphere {
public:
    Sphere();

    dvec3 center;
    float radius;
    dvec3 color;

    Sphere(const dvec3 &center, float radius);

    Sphere(const dvec3 &center, float radius, const dvec3 &color);
};


#endif //RAYTRACER_SPHERE_H
