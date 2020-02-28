#include "scene/point_light.h"

PointLight::PointLight(const Tuple &intensity, const Tuple &position) :
    m_intensity{intensity},
    m_position{position}
{}