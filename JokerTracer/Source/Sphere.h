#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "Vector.h"

namespace NMath
{
	class Sphere
	{
	public:
		Sphere():m_Radius(0), m_Center(0,0,0)
		{

		}

		Sphere(Vector3 center, float r): m_Radius(r), m_Center(center)
		{

		}

	public:
		Vector3 m_Center;
		float	m_Radius;
	};
}
#endif
