//
// Created by ben on 2019-12-06.
//

#ifndef RAY_TRACER_OBJECT_H
#define RAY_TRACER_OBJECT_H

#include "color.h"
#include "vect.h"
#include "ray.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <cfloat>

enum Texture_t {MAT, REFLECTIVE, SPECULAR};

class Object {
public:
    Color_t color;
    Texture_t texture;
    Object(Color_t col, Texture_t text = MAT) : color(col), texture(text) {}
    virtual Vec3 get_normal(const Vec3 &p) const = 0;
    virtual bool intersect(const Ray &ray, double &t) const = 0;
    const double SELF_AVOID_T = 1e-2;
};


class Sphere : public Object {
    Vec3 Center;
    double Radius;
public:
    Sphere(Vec3 center, double radius, Color_t color, Texture_t texture=MAT) : Center(center), Radius(radius), Object(color, texture) {}
    Vec3 get_center() const;
    Vec3 get_normal(const Vec3 &p) const;
    bool intersect(const Ray &ray, double &t) const;
};


class Cylinder : public Object {
    Vec3 center;
    Vec3 direction;
    double radius;
    double height;
public:
    Cylinder(Vec3 _center, Vec3 _direction, double _radius, double _height, Color_t color, Texture_t texture = MAT) :
    center(_center), direction(_direction.normalize()), radius(_radius), height(_height), Object(color, texture) {}
    Vec3 get_center() const;
    Vec3 get_normal(const Vec3 &p) const;
    bool intersect (const Ray &ray, double &t) const;
};


/*class Cone : public Object {
    Vec3 center;
    Vec3 direction;
    double slope;
    double height;
public:
    Cone(Vec3 _center, Vec3 _direction, double _slope, double _height, Color_t color, Texture_t texture = MAT) :
    center(_center), direction(_direction.normalize()), slope(_slope), height(_height), Object(color, texture) {}
    Vec3 get_center() const;
    Vec3 get_normal(const Vec3 &p) const;
    bool intersect(const Ray &ray, double &t) const;
};*/


class Plane : public Object {
protected:
    Vec3 center;
    Vec3 direction;
public:
    Plane(Vec3 _center, Vec3 _direction, Color_t color, Texture_t texture = MAT) :
    center(_center), direction(_direction.normalize()), Object(color, texture) {};
    Vec3 get_center() const {
        return center;
    }
    Vec3 get_normal(const Vec3 &p) const {
        return direction;
    }
    virtual bool intersect(const Ray& ray, double& t) const {
        double directions_dot_prod = direction.dot(ray.direction);
        if (directions_dot_prod == 0) {// the plane and ray are parallel
            t = FLT_MAX; // no intersection, at 'infinity'
            return false;
        }
        t = direction.dot(center - ray.origin) / directions_dot_prod;

        if (t < SELF_AVOID_T) { // the plane is behind the ray
            t = FLT_MAX;
            return false;
        }

        return true;
    }

};


class Circle : public Plane {
    double radius;
public:
    Circle(Vec3 _center, Vec3 _direction, double _radius, Color_t color, Texture_t texture = MAT) :
    radius(_radius), Plane(_center, _direction, color, texture) {}
    bool intersect(const Ray &ray, double &t) const;
};




#endif //RAY_TRACER_OBJECT_H
