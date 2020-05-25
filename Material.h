//
// Created by Roberto on 05/25/20.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "Vectors/Vector3.h"

class Material {
public:
    float specularComponent;
    float reflectionComponent;
    dvec3 diffuseColor;

    Material(float specularComponent, float reflectionComponent, const dvec3 &diffuseColor);

    Material();
};


#endif //RAYTRACER_MATERIAL_H
