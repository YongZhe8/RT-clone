# Tutor's lesson map

This is a reference for keeping lessons structured. It is not a reading assignment.
Use the supplied book version 4.0.2, by section title. Explain only the current
micro-step in the conversation. Rows may span multiple sessions; they are not a
schedule or a demand to cover every listed prerequisite at once.

## Teaching agreement

- Start by stating our current position, today's single goal, and the working file.
- Check understanding locally. Knowing advanced material does not imply remembering
  every prerequisite; a gap does not mean restarting the entire subject.
- Teach the visual/concrete idea before the formula, then relate it to the code.
- Introduce syntax such as references, `const`, casts, constructors, and virtual
  functions at the point of use, with a smaller example when needed.
- Ask one targeted question at a time when the learner is confused. Wait for the
  response before moving on. Do not reveal a complete solution while asking them
  to work it out.
- At natural checkpoints, ask for a prediction, explanation, or small modification.
  Do not quiz after every line. Open-ended checks do not need a quiz interface.
- End with the achieved result and one next step. Update the roadmap progress note.
- The finished reference is a debugging and design anchor, not code the learner
  must copy or memorize. It can evolve; explain meaningful departures from the book.

## Lesson-to-source map

| Lesson | Book section | What we build or examine | Relevant final reference | Checkpoint |
|---|---|---|---|---|
| 0. Compile and run | Output an Image — build context | One tiny `learning/main.cpp` | No renderer file required | Learner can run the executable and change its message |
| 1. One color | Output an Image / The PPM Image Format | RGB values and a minimal image | `color.h`, eventually | Predict a pixel's color from its components |
| 2. A gradient | Creating an Image File | File output and nested loops | `main.cpp` output stream; `camera.h` loops | Explain which loop changes rows and which changes columns |
| 3. Three numbers | The vec3 Class / Color Utility Functions | A small vector class; add operations as needed | `vec3.h`, `color.h` | Distinguish a position, a direction, and an RGB triple |
| 4. A ray and sky | Rays, a Simple Camera, and Background | `origin + t * direction`; a fixed view | `ray.h`, sky branch of `camera.h` | Calculate two points on a ray and explain `t` |
| 5. One sphere | Adding a Sphere | First a hit/miss color, then closest positive intersection | `sphere.h` | Predict a hit and explain why a point behind the camera is rejected |
| 6. Surface direction | Surface Normals and Multiple Objects | Normals, simple normal-based colors, and multiple spheres | `hittable.h`, `sphere.h` | Explain a normal and why the closest object hides a farther one |
| 7. Object interfaces | An Abstraction for Hittable Objects / A List of Hittable Objects / Some New C++ Features / An Interval Class | Object list and shared hit contract | `hittable.h`, `hittable_list.h`, `interval.h` | Explain `virtual`, `override`, and the purpose of a shared pointer in this program |
| 8. Camera organization | Moving Camera Code Into Its Own Class | Move working rendering code into a class | `camera.h` | Identify camera responsibilities without changing the image |
| 9. More than one sample | Antialiasing | Sample nearby rays and average them | sampling loop and `get_ray` in `camera.h` | Predict how more samples affects edge quality and runtime |
| 10. Matte surfaces | Diffuse Materials / Limiting the Number of Child Rays / Fixing Shadow Acne / Gamma Correction | Bounces, bounce limit, a small hit offset, brightness correction | `material.h`, recursive `ray_color`, `color.h` | Trace one bounce and explain what stops recursion |
| 11. Metal | Metal / An Abstract Class for Materials / Mirrored Light Reflection / Fuzzy Reflection | A second material using the same interface | `material.h`, `vec3.h` reflection | Predict a reflection and explain how two materials share an interface |
| 12. Project controls | Our extension beyond the selected book sections | Presets, settings, validation, final demonstration | `scenes.h`, command-line parts of `main.cpp` | Change settings intentionally and explain the resulting image |

We can reorder sampling and material lessons if the learner benefits. The final
reference necessarily combines ideas that will first appear in separate, smaller
learning programs. For example, the first sphere uses a free intersection
function before we teach the final class hierarchy.

## Mathematics at the point of use

- RGB: three component values, scaling, and averages.
- Vectors: positions versus displacements; componentwise arithmetic; length.
- Rays: a starting point plus a scaled direction. `t` is not always distance.
- Sphere intersection: squared distance, dot product, quadratic equation,
  discriminant, and choosing a permitted root. Work a small numerical example.
- Normals: an outward direction perpendicular to the surface, normalized to length 1.
- Reflection: a drawing and a concrete direction before using the formula.
- Sampling: an average of repeated estimates, with no probability-course prerequisite.
- Cross products, camera rotation, and refraction wait for an extension that needs them.

## Working reference flow

`main.cpp` chooses settings and calls `make_scene`. `camera::render` visits pixels,
creates rays, and calls `ray_color`. The world selects the closest sphere hit.
The hit's material returns a bounce direction and a color multiplier. Recursion
continues until a miss returns the sky color or the bounce limit is reached.
Samples are averaged, gamma-corrected, and written to the output file.

This paragraph is a tutor reference, not a lesson-1 explanation to deliver in full.
