# Actual renderer output

Both images were rendered by the included reference at 320 x 180, 60 samples per
pixel, and depth 10. PNG files are convenient conversions of the matching PPMs.

From the project root, after compiling:

```bash
./raytracer --scene mixed --samples 60 --output examples/mixed.ppm
./raytracer --scene matte --samples 60 --output examples/matte.ppm
```

Some noise is expected. The defaults use fewer samples for faster feedback.
