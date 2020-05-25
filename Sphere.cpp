//
// Created by menegais1 on 23/05/2020.
//

#include "Sphere.h"

Sphere::Sphere(const dvec3 &center, float radius) : center(center), radius(radius) {}

Sphere::Sphere(const dvec3 &center, float radius, Material material)
        : center(center), radius(radius),  material(material) {}

Sphere::Sphere() {

}
