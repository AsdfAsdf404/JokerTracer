#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "Vector.h"
#include "Material.h"
namespace Joker
{
	class Material;

	class Sphere
	{
	public:
		Sphere();

		Sphere(Vector3 center, float r, Material* mat);

	public:
		Vector3 m_Center;
		float	m_Radius;
		Material* m_mat;
	};
}
#endif
