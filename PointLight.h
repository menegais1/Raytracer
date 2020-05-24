//
// Created by menegais1 on 23/05/2020.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include "Vectors/Vector3.h"

class PointLight {
public:

    dvec3 position;
    float intensity;

    PointLight(const dvec3 &position, float intensity);
};


#endif //RAYTRACER_POINTLIGHT_H
