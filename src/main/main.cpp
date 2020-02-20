#include <iostream>
#include "common.h"
#include "math/tuple.h"
#include "math/matrix.h"
#include "core/ray.h"
#include "image/framebuffer.h"
#include "primitives/sphere.h"
#include "primitives/intersection.h"

int main()
{
    Sphere s1;
    Sphere s2;
    Tuple p = point(0.0, 0.0, 0.0);
    Tuple v = vector(1.0, 0.0, 0.0);

    Tuple p1 = point(-3.0, 0.0, 0.0);
    Tuple v1 = vector(1.0, 0.0, 0.0);
    Ray r{p, v};
    Ray r2{p1, v1};
    std::vector<Intersection> intersects = intersections(r, s1);
    std::vector<Intersection> intersects2 = intersections(r2, s2);
    for (int i = 0; i < intersects.size(); i++)
	std::cout << intersects.at(i).t() << "\t";
    std::cout << std::endl;
    for (int i = 0; i < intersects2.size(); i++)
	std::cout << intersects2.at(i).t() << "\t";
    std::cout << std::endl;
   
    Intersection* i = hit(intersects);
    Intersection* i2 = hit(intersects2);
    std::cout << i->object().id() << "\t" << i->t() << "\n";
    std::cout << i2->object().id() << "\t" << i2->t();
    return 1;
}