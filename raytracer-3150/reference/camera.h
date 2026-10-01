#ifndef CAMERA_H
#define CAMERA_H

// Teaching adaptation of Ray Tracing in One Weekend (Shirley, Black, Hollasch).
// The supplied reference code carries a CC0 public-domain dedication.
// See ../docs/SOURCES.md. This camera stays at the origin, looking along -Z.

#include "hittable.h"
#include "material.h"
#include <ostream>
#include <stdexcept>

class camera {
  public:
    int image_width = 320;
    int image_height = 180;
    int samples_per_pixel = 20;
    int max_depth = 10;

    void render(const hittable& world, std::ostream& out) {
        initialize();
        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = 0; j < image_height; ++j) {
            for (int i = 0; i < image_width; ++i) {
                color pixel_color(0, 0, 0);
                for (int sample = 0; sample < samples_per_pixel; ++sample) {
                    ray r = get_ray(i, j);
                    pixel_color += ray_color(r, max_depth, world);
                }
                // Average BEFORE correcting brightness and writing bytes.
                write_color(out, pixel_color / samples_per_pixel);
            }
        }
    }

  private:
    point3 center = point3(0, 0, 0);
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    void initialize() {
        if (image_width < 1 || image_width > 4096 ||
            image_height < 1 || image_height > 4096 ||
            samples_per_pixel < 1 || samples_per_pixel > 1000 ||
            max_depth < 1 || max_depth > 100)
            throw std::invalid_argument("Render settings are outside the supported ranges.");

        // A rectangle one unit in front of the camera represents our view.
        double viewport_height = 2.0;
        double viewport_width = viewport_height * double(image_width) / image_height;
        vec3 viewport_u(viewport_width, 0, 0);
        vec3 viewport_v(0, -viewport_height, 0); // Image rows run downward.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;
        point3 upper_left = center - vec3(0, 0, 1) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i, int j) const {
        // Nearby rays estimate the average color across this pixel's area.
        double offset_x = random_double() - 0.5;
        double offset_y = random_double() - 0.5;
        point3 sample = pixel00_loc
                      + (i + offset_x) * pixel_delta_u
                      + (j + offset_y) * pixel_delta_v;
        return ray(center, sample - center);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
        if (depth <= 0) return color(0, 0, 0);
        hit_record rec;
        // Skip immediate self-intersections after a bounce.
        if (world.hit(r, interval(0.001, infinity), rec)) {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1, world);
            return color(0, 0, 0);
        }
        vec3 direction = unit_vector(r.direction());
        double blend = 0.5 * (direction.y() + 1.0);
        return (1.0 - blend) * color(1.0, 1.0, 1.0)
             + blend * color(0.5, 0.7, 1.0);
    }
};

#endif
