# CSE 3150 Ray Tracer — Teaching Reference v1

Start with **Roadmap.md**. You are not expected to read the finished source now.

This package gives our lessons a concrete, working destination. We will build your
own learning version in small steps, using this reference to explain and check it.
The reference can change as your understanding, team, and course requirements develop.

## What is here

| Location | Purpose | When to open it |
|---|---|---|
| `Roadmap.md` | Short learning plan and current position | Now |
| `learning/` | Place for the code you will write during lessons | When we start coding |
| `reference/` | Complete simplified renderer | Only the file relevant to the current lesson |
| `book-reference/` | All 11 supplied source files, with their original filenames and unchanged contents | To compare with the book or restore optional features |
| `docs/LESSONS.md` | Detailed lesson-to-source map for the tutor | As needed; not assigned reading |
| `docs/TEAM.md` | Suggested ownership for 2–4 people | After the first sphere |
| `docs/SOURCES.md` | Attribution and adaptation notes | When preparing project documentation |
| `docs/VERIFICATION.md` | Checks actually performed | When evaluating the reference |
| `tests/` | Small checks for geometry, materials, and invalid settings | When those ideas have been taught |
| `examples/` | Images produced by this implementation | Optional preview |

## Completed reference features

The renderer writes a P3 PPM image of spheres and a ground surface. It supports
matte and reflective/fuzzy metal materials, sky lighting, multiple samples per
pixel, a bounce limit, gamma correction, two scene presets, and command-line
settings. It runs on the CPU and needs only a C++17 compiler and the standard library.

The camera is fixed at the origin, looking along negative Z. Glass, a movable
camera, defocus blur, multithreading, and a GUI are outside this first target.
They are possible later additions, not prerequisites for reaching this target.

## Optional: run the finished reference

These commands are for an existing GCC-compatible C++17 setup, from this folder.
We will adapt setup instructions to your actual computer during lesson 0.

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic reference/main.cpp -o raytracer
./raytracer --output mixed.ppm
./raytracer --scene matte --output matte.ppm
```

For a small preview:

```bash
./raytracer --width 160 --height 90 --samples 5 --output preview.ppm
```

For a less noisy image:

```bash
./raytracer --width 640 --height 360 --samples 100 --output detailed.ppm
```

The program writes the file itself; shell output redirection is unnecessary.
Use `--help` to see the ranges and defaults. The named output file is replaced
when you render again. Choose a new name to keep a previous image.

PPM is the book's deliberately simple image format. Your default photo app may
not open it; the included PNG examples can be viewed directly. Opening or
converting your own PPM will be part of our first image lesson.

## Optional: run the core checks

```bash
g++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -Ireference tests/core_tests.cpp -o core_tests
./core_tests
```

## How we will use this

We start with a tiny program in `learning/`, adding only the concepts needed for
the current result. Reaching the first sphere does not mean you must already
understand materials, sampling, or the completed reference's command-line parser.

The source uses the book's names where practical so we can move between them.
The header-oriented layout also follows the book. Separating implementation into
additional `.cpp` files is a later team decision, not a lesson-1 requirement.

The supplied book is version 4.0.2, dated 2025-04-25. Its main section titles
identify readings in our lesson map, avoiding PDF page-number differences.
The book itself remains among your existing attachments.

This is an instructional reference, not evidence that you or your teammates
have already completed the work. Final project scope and disclosure expectations
will be aligned with your actual course rubric when it is available.
