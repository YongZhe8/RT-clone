// Completed teaching reference: this is our destination, not the first lesson.
#include "camera.h"
#include "scenes.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

int read_integer(const std::string& text, int minimum, int maximum,
                 const std::string& option) {
    std::size_t used = 0;
    int value;
    try {
        value = std::stoi(text, &used);
    } catch (const std::exception&) {
        throw std::invalid_argument(option + " needs an integer.");
    }
    if (used != text.size() || value < minimum || value > maximum)
        throw std::invalid_argument(option + " must be between "
            + std::to_string(minimum) + " and " + std::to_string(maximum) + ".");
    return value;
}

void print_help() {
    std::cout
        << "Usage: raytracer [options]\n"
        << "  --scene mixed|matte   Scene preset (default: mixed)\n"
        << "  --width N             Image width, 1..4096 (default: 320)\n"
        << "  --height N            Image height, 1..4096 (default: 180)\n"
        << "  --samples N           Samples per pixel, 1..1000 (default: 20)\n"
        << "  --depth N             Maximum ray bounces, 1..100 (default: 10)\n"
        << "  --output PATH         Image file (default: render.ppm; replaces it)\n"
        << "  --help                Show this help\n";
}

int main(int argc, char* argv[]) {
    try {
        camera cam;
        std::string scene_name = "mixed";
        std::string output_path = "render.ppm";
        for (int i = 1; i < argc; ++i) {
            std::string option = argv[i];
            if (option == "--help") {
                print_help();
                return 0;
            }
            if (option != "--scene" && option != "--output" && option != "--width" &&
                option != "--height" && option != "--samples" && option != "--depth")
                throw std::invalid_argument("Unknown option: " + option);
            if (i + 1 >= argc)
                throw std::invalid_argument("Missing value after " + option);
            std::string value = argv[++i];
            if (option == "--scene") scene_name = value;
            else if (option == "--output") output_path = value;
            else if (option == "--width")
                cam.image_width = read_integer(value, 1, 4096, option);
            else if (option == "--height")
                cam.image_height = read_integer(value, 1, 4096, option);
            else if (option == "--samples")
                cam.samples_per_pixel = read_integer(value, 1, 1000, option);
            else if (option == "--depth")
                cam.max_depth = read_integer(value, 1, 100, option);
        }
        // Repeated renders are reproducible on the same C++ implementation.
        std::srand(42);
        hittable_list world = make_scene(scene_name);
        std::ofstream image_file(output_path);
        if (!image_file)
            throw std::runtime_error("Cannot open output file: " + output_path);
        std::clog << "Rendering " << scene_name << " (" << cam.image_width << 'x'
                  << cam.image_height << ", " << cam.samples_per_pixel
                  << " samples per pixel)...\n";
        cam.render(world, image_file);
        image_file.close();
        if (!image_file)
            throw std::runtime_error("Could not finish writing the image.");
        std::clog << "Saved " << output_path << '\n';
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << "\nRun with --help for options.\n";
        return 1;
    }
}
