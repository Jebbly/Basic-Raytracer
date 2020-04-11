# A Basic Raytracer using the Standard Library
This is a basic offline raytracer written in C++ with only the use of the standard library. It was primarily developed as a learning experience to practice C++ development and understand the fundamentals of raytracing.

## Features
The raytracer can import simple .OBJ models with or without normal interpolation. Shapes can be grouped together in an axis-aligned bounding box as an acceleration structure, which is especially useful when importing 3d models with high tri-counts. The supported procedural shapes include:
- Cones
- Cubes
- Cylinders
- Planes
- Spheres

These shapes can be assigned color or pattern materials. The Phong BRDF is used as the shading model and it also supports reflection and refraction using Schlick approximation for the Fresnel factor.

There is also support for multiple lights, so a rendered scene can include a combination of directional, point, and spot lights.

## Examples
Glass Sphere (4000x4000): 1125-second render time
![Glass_Sphere](https://github.com/Jebbly/Basic-Raytracer/blob/master/examples/glass_sphere.png)

Patterned Spheres (3840x2160): 158-second render time
![Patterned_Spheres](https://github.com/Jebbly/Basic-Raytracer/blob/master/examples/sphere_patterns.png)

## Building
To setup the project for compilation after cloning, type:
```
cd basic-raytracer
mkdir build
cd build
cmake ..
```

## To-do List
- Implement Multithreading
- Move All Accessor Methods from Header Files to Source Files
- Clean Up Tuple and Matrix Classes
- Sort Includes in All Headers
- Comment All Logic
- Implement Commands

## Additional Resources
[Fast, Minimum Storage Ray/Triangle Intersection](https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf)

[Ray-Primitive Intersections](https://www.iquilezles.org/www/articles/intersectors/intersectors.htm)

[Raytracer Challenge by Jamis Buck](http://raytracerchallenge.com/)

[Reflections and Refractions in Ray Tracing](https://graphics.stanford.edu/courses/cs148-10-summer/docs/2006--degreve--reflection_refraction.pdf)
