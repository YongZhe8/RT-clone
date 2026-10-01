#ifndef SCENES_H
#define SCENES_H

// New teaching-project code. See ../docs/SOURCES.md.
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include <stdexcept>
#include <string>

inline hittable_list make_scene(const std::string& name) {
    if (name != "mixed" && name != "matte")
        throw std::invalid_argument("Unknown scene. Choose mixed or matte.");
    hittable_list world;
    auto ground = make_shared<lambertian>(color(0.65, 0.65, 0.65));
    auto blue = make_shared<lambertian>(color(0.15, 0.35, 0.75));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, ground));
    world.add(make_shared<sphere>(point3(0, 0, -1.3), 0.5, blue));
    if (name == "mixed") {
        auto silver = make_shared<metal>(color(0.8, 0.85, 0.9), 0.0);
        auto gold = make_shared<metal>(color(0.85, 0.6, 0.2), 0.25);
        world.add(make_shared<sphere>(point3(-1.05, 0, -1.3), 0.5, silver));
        world.add(make_shared<sphere>(point3(1.05, 0, -1.3), 0.5, gold));
    } else {
        auto red = make_shared<lambertian>(color(0.7, 0.15, 0.15));
        auto green = make_shared<lambertian>(color(0.15, 0.65, 0.25));
        world.add(make_shared<sphere>(point3(-1.05, 0, -1.3), 0.5, red));
        world.add(make_shared<sphere>(point3(1.05, 0, -1.3), 0.5, green));
    }
    return world;
}

#endif
