//
// Created by menegais1 on 23/05/2020.
//

#include "Ray.h"
#include "Sphere.h"

Ray::Ray(const dvec3 &origin, const dvec3 &direction) : origin(origin), direction(direction) {}

bool Ray::raySphereIntersection(Sphere s, dvec3 &point) {
    dvec3 oc = s.center - origin;
    if (oc.dot(direction) <= 0) {
        point = dvec3(0, 0, 0);
        return false;
    }
    float rayLength = direction.length();
    dvec3 projection = direction * (oc.dot(direction) / (rayLength * rayLength));
    dvec3 pointInsideSphere = origin + projection;
    float distance = (pointInsideSphere - s.center).length();
    if (distance < s.radius) {
        float c = s.radius;
        float a = distance;
        float b = std::sqrt(c * c - a * a);
        point = pointInsideSphere - direction.unit() * b;
        return true;
    } else if (distance == s.radius) {
        point = origin + projection;
        return true;
    }

    return false;
}
