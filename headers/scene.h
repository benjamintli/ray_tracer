//
// Created by ben on 2019-12-07.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H

#include "object.h"
#include "color.h"
#include <iostream>
#include <list>

using namespace std;

class Lightsource {
public:
    Vec3 position;
    Color_t color;
    double intensity = 100;
    Lightsource(Vec3 _position, Color_t _color = Color_t(255, 255, 255), double _intensity = 100.0) : position(_position), color(_color), intensity(_intensity) {};
};

class Scene {
    list<Object*> objects;
    list<Lightsource> lightsources;
public:
    void add(Object *object);

    void add(Lightsource light);

    Color_t shading(const Ray& ray, const Object &object, double t, int depth);

    Color_t trace(int x, int y);

    Color_t trace_ray(const Ray &ray, const Object * exclude_obj, int depth);

    bool check_occlusion(Vec3 target, Vec3 source);
};

#endif //RAY_TRACER_SCENE_H
