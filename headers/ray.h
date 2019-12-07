//
// Created by ben on 2019-12-06.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "vect.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray(Vec3 org, Vec3 dir) : origin(org), direction(dir) {}

    Vec3 get_point(double t) const{
        return origin + direction * t;
    }

    Vec3 reflect_by(const Vec3 &normal) const{
        return direction - normal * normal.dot(direction) * 2;
    }
};

#endif //RAY_TRACER_RAY_H
