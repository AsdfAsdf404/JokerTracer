#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include "Vector.h"
#include "Ray.h"

#include <vector>

namespace Joker
{
	class Sphere;
	class Material;
	class hit_record
	{
	public:
		float t;
		Vector3 point;
		Vector3 normal;
		Material * material;
	};

	double drand48(void);

	Vector3 randomInSphere();

	class hitable
	{
	public:
		virtual bool hit(const Ray & ray, float tmin, float tmax, hit_record& hit) const = 0;
	};

	class Intersect
	{
	public:
		static bool isIntersect(const Ray & ray, const Sphere & sphere, float tmax, float tmin, hit_record& intersectpoint);
	};

	class hitable_list : public hitable
	{
	public:
		hitable_list();
		hitable_list(std::vector< Sphere* > &list);

		virtual bool hit(const Ray & ray, float tmin, float tmax, hit_record& hit)const;

	private:
		std::vector< Sphere* > m_list;
	};

}
#endif
