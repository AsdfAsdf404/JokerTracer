#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include "Vector.h"
#include "Ray.h"

#include "Sphere.h"
#include <vector>

namespace NMath
{
	class hit_record
	{
	public:
		float t;
		Vector3 point;
		Vector3 normal;
	};

	class hitable
	{
	public:
		virtual bool hit(const Ray & ray, float tmin, float tmax, hit_record& hit) const = 0;
	};

	
	

	class Intersect
	{
	public:
		static bool isIntersect(const Ray & ray, const Sphere & sphere,float tmax, float tmin, hit_record& intersectpoint)
		{
			Vector3 oc = ray.getPosition() - sphere.m_Center;

			float a = dot(ray.getDirction(), ray.getDirction());
			float b = dot(oc, ray.getDirction());
			float c = dot(oc, oc) - sphere.m_Radius * sphere.m_Radius;

			float discriminant = b * b -  a *c;
			if (discriminant > 0)
			{
				float temp = (-b - sqrt(b *b -  a *c)) / a;
				if (temp > tmin && temp < tmax)
				{
					intersectpoint.t = temp;
					intersectpoint.point = ray.getPoint(temp);
					intersectpoint.normal = (intersectpoint.point - sphere.m_Center) / sphere.m_Radius;
					return true;
				}

				temp = (-b + sqrt(b *b - a *c)) / a;
				if (temp > tmin && temp < tmax)
				{
					intersectpoint.t = temp;
					intersectpoint.point = ray.getPoint(temp);
					intersectpoint.normal = (intersectpoint.point - sphere.m_Center) / sphere.m_Radius;
					return true;
				} 
			}

			return false;
		}
	};


	class hitable_list : public hitable
	{
	public:
		hitable_list() {}
		hitable_list(std::vector<Sphere*> &list) {
			m_list.assign(list.begin(), list.end());
		}

		virtual bool hit(const Ray & ray, float tmin, float tmax, hit_record& hit)const
		{
			hit_record temp_rec;
			bool hit_anything = false;
			double closed_so_far = tmax;

			for (int i = 0; i < m_list.size(); i++)
			{
				if (Intersect::isIntersect(ray, *m_list[i], closed_so_far, tmin, temp_rec))
				{
					hit_anything = true;
					closed_so_far = temp_rec.t;
					hit = temp_rec;
				}
			}

			return hit_anything;
		}

	private:
		std::vector<Sphere*> m_list;
	};

}
#endif
