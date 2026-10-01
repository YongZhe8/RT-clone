# Sources and adaptation notes

Prepared for YongZhe's CSE 3150 learning project on 2026-09-23.

## Source supplied by the user

**Ray Tracing in One Weekend**, Peter Shirley, Trevor David Black, and Steve Hollasch.
The supplied HTML identifies version **4.0.2**, dated **2025-04-25**.
Canonical book address for attribution:
https://raytracing.github.io/books/RayTracingInOneWeekend.html

This package was prepared from the supplied local book and source attachments;
it does not claim to track a newer online edition. The book text is not reproduced
in this package. It remains in the user's original attachments.

`book-reference/` contains exact copies of the eleven supplied code files, with
the scratch attachment number prefixes removed from the filenames. No source
contents were edited in that folder. `SOURCE_MANIFEST.json` records their hashes
and associated attachment identities for later comparison.

The source-file notices dedicate the original software to the public domain
under CC0 and disclaim warranty. Those notices are preserved in the copied files
and the retained adapted headers. The notice refers to an upstream `COPYING.txt`,
which was not included among the uploaded attachments. A copy of that file is
not being represented as supplied here. The code dedication and book-text
copyright should not be confused.

## Teaching adaptation

`reference/` was assembled and adapted with ChatGPT assistance for this learning
plan. It is explicitly based on the supplied book code, not represented as a
student's independently completed work.

Main changes:

- Use a fixed camera at the origin facing negative Z, with no defocus calculations.
- Keep matte (`lambertian`) and metal materials. Remove glass and unused vector
  helpers associated with later camera/refraction chapters.
- Use four spheres per scene (including the large ground sphere) instead of a
  randomized field of hundreds of spheres.
- Add `scenes.h` with two presets and a new `main.cpp` with validated render controls.
- Write to an explicit file stream instead of redirecting image data from stdout.
- Keep book terminology and its header-oriented layout to simplify comparison.
- Make headers self-contained and use inline header definitions where needed so
  including them from multiple C++17 translation units does not duplicate symbols.
- Reject invalid sphere radii, missing materials, and unsupported camera settings.
- Make the material base class abstract and keep the two implementations small.
- Use a fixed random seed for repeatable debugging within the same C++ implementation.
- Add focused correctness checks, sample output, and the teaching/team maps.

New material in this package can be revised as learning and requirements evolve.
Record substantial changes here rather than pretending they came from the book.
