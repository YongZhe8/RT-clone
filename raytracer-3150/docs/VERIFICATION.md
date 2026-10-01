# Reference verification

Checked on 2026-09-23 using GCC 13.3.0 on Linux.

## Results

- Teaching reference and core checks compiled as C++17 with `-O2 -Wall -Wextra
  -Wpedantic -Werror`, with no warnings or errors.
- Core checks passed for a direct sphere hit, a miss, an inside-sphere exit,
  excluded interval endpoint, correct normal orientation, closest-hit selection
  in both insertion orders, matte scatter direction/color, exact mirror
  reflection, gamma/color conversion, zero-radius rejection, and invalid settings.
- Both `mixed` and `matte` scenes rendered successfully at 320 x 180 with 60
  samples per pixel and a bounce limit of 10. Their PPM headers, component counts,
  integer ranges, and nonconstant image data were checked.
- `examples/mixed.png` and `examples/matte.png` are format conversions of those
  PPM outputs, not separately generated artwork. The mixed image was visually
  inspected for the expected three foreground spheres, ground, and sky.
- Ten invalid command-line/input-output cases returned a failure with an error
  message. Help returned successfully. A 1 x 1 render was valid and repeatable.
- The adapted headers linked successfully when included from two translation units.
- The unchanged supplied book source compiled. Its large final scene was not rendered.
- Before packaging, the original source copies were compared byte-for-byte with
  the uploaded source, and the archive was checked for integrity.

## Scope

This verifies the packaged reference, not an as-yet-unwritten student version.
The compiler/editor on your computer has not been identified or tested yet.
The fixed random seed supports repeatability on the same C++ implementation;
different standard libraries can produce different sample sequences.

Samples are intentionally modest. Some visible grain is expected from stochastic
sampling and can be reduced with more samples. This CPU renderer prioritizes
clarity over speed and does not promise interactive rendering.
