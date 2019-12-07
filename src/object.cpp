//
// Created by ben on 2019-12-06.
//

#include "../headers/object.h"

//sphere
Vec3 Sphere::get_center() const{
    return Center;
}

Vec3 Sphere::get_normal(const class Vec3 & p) const {
    return ((p - Center) * (-1 / Radius)).normalize();
}

bool Sphere::intersect(const class Ray & ray, double & t) const {
    Vec3 v = ray.origin - Center;

    const double b = 2 * v.dot(ray.direction);
    const double c = v.dot(v) - Radius * Radius;
    double delta = b*b - 4 * c;

    if (delta < 0) {
        t = FLT_MAX;
        return false;
    }

    const double t1 = (-b - sqrt(delta))/2;
    const double t2 = (-b + sqrt(delta))/2;

    if (t2 < SELF_AVOID_T) {
        t = FLT_MAX;
        return false;
    }

    t = (t1 >= SELF_AVOID_T) ? t1 : t2;

    return true;
}

//cylinder
Vec3 Cylinder::get_center() const {
    return center;
}

Vec3 Cylinder::get_normal(const class Vec3 & p) const {
    Vec3 to_center = p - center;
    return ((to_center - direction*(to_center.dot(direction))).normalize());
}

bool Cylinder::intersect(const Ray &ray, double & t) const {
    Vec3 rel_origin = ray.origin - center;

    const double direction_dot = ray.direction.dot(direction);
    const double a = 1 - direction_dot * direction_dot;
    const double b = 2 * (rel_origin.dot(ray.direction) - direction_dot * rel_origin.dot(direction));
    const double c = rel_origin.dot(rel_origin) - rel_origin.dot(direction) * rel_origin.dot(direction) - radius * radius;

    double delta = b * b - 4 * a * c;

    if (delta < 0) {
        t = FLT_MAX;
        return false;
    }

    const double sqrt_delta_2a = sqrt(delta) / (2 * a);
    double t1 = (-b) / (2*a);
    const double t2 = t1 + sqrt_delta_2a;
    t1 -= sqrt_delta_2a;

    if (t2 < SELF_AVOID_T) { // the cylinder is behind us
        t = FLT_MAX; // no intersection, at 'infinity'
        return false;
    }

    double center_proj = center.dot(direction);
    double t1_proj = ray.get_point(t1).dot(direction);
    if (t1 >= SELF_AVOID_T && t1_proj > center_proj && t1_proj < center_proj+height) {
        t = t1;
        return true;
    }

    double t2_proj = ray.get_point(t2).dot(direction);
    if (t2 >= SELF_AVOID_T && t2_proj > center_proj && t2_proj < center_proj+height) {
        t = t2;
        return true;
    }

    t = FLT_MAX; // no intersection, at 'infinity'
    return false;
}

bool Circle::intersect(const Ray &ray, double & t) const {
    if (!Plane::intersect(ray, t)) { // the ray doesnt even hit the plane
        return false;
    }
    Vec3 intersect_point = ray.get_point(t);

    if ((intersect_point - center).norm2() > radius*radius) { // intersects with plane outside circle
        t = FLT_MAX;
        return false;
    }

    return true;
}