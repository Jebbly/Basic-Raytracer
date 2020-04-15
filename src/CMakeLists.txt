set(CORE_SRCS
    core/bounding_box.cpp
    core/computation.cpp
    core/intersection.cpp
    core/ray.cpp
)

set(GEOMETRY_SRCS
    geometry/primitives/cone.cpp
    geometry/primitives/cube.cpp
    geometry/primitives/cylinder.cpp
    geometry/primitives/plane.cpp
    geometry/primitives/primitive.cpp
    geometry/primitives/smooth_triangle.cpp
    geometry/primitives/sphere.cpp
    geometry/primitives/triangle.cpp
    geometry/csg.cpp
    geometry/group.cpp
    geometry/mesh.cpp
)

set(IMAGE_SRCS
    image/camera.cpp
    image/color.cpp
    image/framebuffer.cpp
)

set(MATERIAL_SRCS
    material/patterns/checker_material.cpp
    material/patterns/gradient_material.cpp
    material/patterns/pattern.cpp
    material/patterns/ring_material.cpp
    material/patterns/stripe_material.cpp
    material/color_material.cpp
    material/material.cpp
)

set(MATH_SRCS
    math/matrix.cpp
    math/tuple.cpp
)

set(SCENE_SRCS
    scene/lights/directional_light.cpp
    scene/lights/light.cpp
    scene/lights/point_light.cpp
    scene/lights/spot_light.cpp
    scene/world.cpp
)

set(UTILITY_SRCS
    utility/helper.cpp
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
