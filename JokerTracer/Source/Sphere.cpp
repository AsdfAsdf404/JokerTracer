#include "Sphere.h"



Joker::Sphere::Sphere(Vector3 center, float r, Material* mat) : m_Radius(r), m_Center(center), m_mat(mat)
{

}

Joker::Sphere::Sphere() : m_Radius(0), m_Center(0, 0, 0)
{

}
