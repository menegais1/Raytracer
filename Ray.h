//
// Created by menegais1 on 23/05/2020.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "Vectors/Vector3.h"
#include "Sphere.h"

class Ray {
public:
    dvec3 origin;
    dvec3 direction;

    Ray(const dvec3 &origin, const dvec3 &direction);

    //Based on: http://www.lighthouse3d.com/tutorials/maths/ray-sphere-intersection/
    bool raySphereIntersection(Sphere s, dvec3 &point);
    
};


#endif //RAYTRACER_RAY_H
