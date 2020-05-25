//
// Created by Roberto on 05/25/20.
//

#include "Material.h"

Material::Material(float specularComponent, float reflectionComponent, const dvec3 &diffuseColor) : specularComponent(
        specularComponent), reflectionComponent(reflectionComponent), diffuseColor(diffuseColor) {}

Material::Material() : specularComponent(0), reflectionComponent(0), diffuseColor(dvec3(0, 0, 0)) {}
