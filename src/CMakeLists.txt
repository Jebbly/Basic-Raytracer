set(CORE_SRCS
    core/bounding_box.cpp
    core/bounding_box.h
    core/computation.cpp
    core/computation.h
    core/intersection.cpp
    core/intersection.h
    core/ray.cpp
    core/ray.h
)

set(GEOMETRY_SRCS
    geometry/primitives/cone.cpp
    geometry/primitives/cone.h
    geometry/primitives/cube.cpp
    geometry/primitives/cube.h
    geometry/primitives/cylinder.cpp
    geometry/primitives/cylinder.h
    geometry/primitives/plane.cpp
    geometry/primitives/plane.h
    geometry/primitives/primitive.cpp
    geometry/primitives/primitive.h
    geometry/primitives/smooth_triangle.cpp
    geometry/primitives/smooth_triangle.h
    geometry/primitives/sphere.cpp
    geometry/primitives/sphere.h
    geometry/primitives/triangle.cpp
    geometry/primitives/triangle.h
    geometry/csg.cpp
    geometry/csg.h
    geometry/group.cpp
    geometry/group.h
    geometry/mesh.cpp
    geometry/mesh.h
)

set(IMAGE_SRCS
    image/camera.cpp
    image/camera.h
    image/framebuffer.cpp
    image/framebuffer.h
)

set(MATERIAL_SRCS
    material/patterns/checker_material.cpp
    material/patterns/checker_material.h
    material/patterns/gradient_material.cpp
    material/patterns/gradient_material.h
    material/patterns/pattern.cpp
    material/patterns/pattern.h
    material/patterns/ring_material.cpp
    material/patterns/ring_material.h
    material/patterns/stripe_material.cpp
    material/patterns/stripe_material.h
    material/color_material.cpp
    material/color_material.h
    material/material.cpp
    material/material.h
)

set(MATH_SRCS
    math/matrix.h
    math/tuple.h
)

set(SCENE_SRCS
    scene/lights/directional_light.cpp
    scene/lights/directional_light.h
    scene/lights/light.cpp
    scene/lights/light.h
    scene/lights/point_light.cpp
    scene/lights/point_light.h
    scene/lights/spot_light.cpp
    scene/lights/spot_light.h
    scene/world.cpp
    scene/world.h
)

set(UTILITY_SRCS
    utility/constants.h
    utility/helper.cpp
    utility/helper.h
)

list(APPEND RAYTRACER_SRCS
    ${CORE_SRCS}
    ${GEOMETRY_SRCS}
    ${IMAGE_SRCS}
    ${MATERIAL_SRCS}
    ${MATH_SRCS}
    ${SCENE_SRCS}
    ${UTILITY_SRCS}
)

add_executable(raytracer main.cpp;${RAYTRACER_SRCS})
