#ifndef PARTICLE_H
#define PARTICLE_H

#include "glm/ext.hpp"


class Particle
{
public:

    Particle();

    void updatePos();
    glm::vec3 m_Pos;
    glm::vec3 m_OldPos;
    glm::vec3 m_Acc;
    int m_Movable;

    glm::vec3 SphereIntersect(float radius);

    void HoleIntersect(float radius);

    void FloorIntersect();

private:




};

#endif // PARTICLE_H
