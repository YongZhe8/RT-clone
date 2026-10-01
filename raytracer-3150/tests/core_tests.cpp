// Optional reference checks, not assigned reading for lesson 1.
#include "scenes.h"
#include "camera.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
bool close(double a, double b) { return std::fabs(a - b) < 1e-9; }

int main() {
    try {
        auto matte = make_shared<lambertian>(color(0.2, 0.4, 0.6));
        sphere ball(point3(0, 0, -1), 0.5, matte);
        hit_record rec;
        ray forward(point3(0, 0, 0), vec3(0, 0, -1));
        require(ball.hit(forward, interval(0.001, infinity), rec), "Expected sphere hit");
        require(close(rec.t, 0.5) && close(rec.p.z(), -0.5), "Wrong nearest root");
        require(rec.front_face && close(rec.normal.z(), 1), "Wrong outside normal");
        require(!ball.hit(ray(point3(0,0,0), vec3(0,1,0)), interval(0.001, infinity), rec),
                "Expected a miss");
        require(ball.hit(ray(point3(0,0,-1), vec3(0,0,1)), interval(0.001, infinity), rec),
                "Ray inside sphere must reach its exit");
        require(!rec.front_face && close(rec.normal.z(), -1), "Wrong inside normal");
        require(!ball.hit(forward, interval(0.001, 0.5), rec), "Open interval bound ignored");
        hittable_list world;
        world.add(make_shared<sphere>(point3(0,0,-3), 0.5, matte));
        world.add(make_shared<sphere>(point3(0,0,-1), 0.5, matte));
        require(world.hit(forward, interval(0.001, infinity), rec) && close(rec.t, 0.5),
                "World must return the closest hit");
        hittable_list reverse_order;
        reverse_order.add(world.objects[1]);
        reverse_order.add(world.objects[0]);
        require(reverse_order.hit(forward, interval(0.001, infinity), rec) && close(rec.t,0.5),
                "Closest hit must not depend on insertion order");
        ray scattered;
        color attenuation;
        std::srand(42);
        require(matte->scatter(forward, rec, attenuation, scattered), "Matte scatter failed");
        require(dot(scattered.direction(), rec.normal) > 0, "Matte ray points inward");
        require(close(attenuation.y(), 0.4), "Matte color not preserved");
        metal mirror(color(0.8,0.8,0.8), 0);
        require(mirror.scatter(forward, rec, attenuation, scattered), "Mirror scatter failed");
        require(close(scattered.direction().z(), 1), "Wrong mirror reflection");
        bool rejected = false;
        try { sphere invalid(point3(0,0,0), 0, matte); }
        catch (const std::invalid_argument&) { rejected = true; }
        require(rejected, "Zero-radius sphere must be rejected");
        std::ostringstream color_output;
        write_color(color_output, color(0.25, 0, 1));
        require(color_output.str() == "128 0 255\n", "Gamma or color conversion failed");
        camera cam;
        cam.image_width = 0;
        rejected = false;
        try { cam.render(world, color_output); }
        catch (const std::invalid_argument&) { rejected = true; }
        require(rejected, "Invalid camera settings must be rejected");
        std::cout << "Core checks passed: intersections, closest hit, normals, materials, color, settings.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Check failed: " << error.what() << '\n';
        return 1;
    }
}
