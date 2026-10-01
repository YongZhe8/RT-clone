# Group roles, after the first sphere

Everyone should first understand a pixel, a ray, and a hit. Agree on the hit
record and material interface together before separating work. Shared foundations
are `vec3`, `ray`, and the meaning of a hit record. No one should own the entire
project merely because they started earlier.

| Role | Main ownership | A demonstrable result |
|---|---|---|
| A: Objects and intersections | `sphere.h`, `hittable.h`, `hittable_list.h`, hit-range use | Nearest object selected correctly; miss and inside-sphere cases explained |
| B: Materials | `material.h`, reflection helper with shared review | Matte and metal use the same interface; bounce directions are sensible |
| C: Camera and rendering | `camera.h`, `color.h` | Correct image dimensions, samples, bounce limit, and brightness conversion |
| D: Scenes and controls | `scenes.h`, `main.cpp` | User selects a scene and image quality; invalid input produces a useful error |

| Team size | Initial split |
|---|---|
| 2 | One person owns A+B; one owns C+D. Rebalance after a small working milestone. |
| 3 | A, B, and C each have an owner; split D into scene building, settings, and integration. |
| 4 | One primary owner per role, with a reviewer from another role. |

These assignments are for understanding and implementing the group's own learning
version. The existence of completed teaching reference code is not evidence of
any student's contribution.

Keep a working shared version. Integrate one small feature at a time and run a
tiny scene. Each owner explains their module; everyone helps test and present.
Review responsibilities whenever the workload becomes uneven. Avoid making one
member responsible only for slides or assigning all mathematics to one person.

The camera calls the object interface; object hits identify a material; the
material supplies the next ray. Preserve those shared interfaces when working
independently. If we later split headers into `.cpp` files, agree on that change
as a team before moving implementations.

Add at most one extension at a time after the core works. Which extensions count
as sufficient original work depends on the actual course rubric; no grade or
approval is implied by this plan.
