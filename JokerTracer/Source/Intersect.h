#ifndef __INTERSECT_H__
#define __INTERSECT_H__

#include "Vector.h"
#include "Ray.h"

#include "Sphere.h"

namespace NMath
{

	class IntersectPoint
	{
	public:
		float t;
		Vector3 point;
		Vector3 normal;
	};

	class Intersect
	{
	public:
		static float isIntersect(const Ray & ray, const Sphere & sphere)
		{
			Vector3 oc = ray.getPosition() - sphere.m_Center;
			float a = dot(ray.getDirction(), ray.getDirction());
			float b = 2 * dot(oc, ray.getDirction());
			float c = dot(oc, oc) - sphere.m_Radius * sphere.m_Radius;
			float discriminant = b * b - 4 * a *c;
			if (discriminant > 0)
			{
				return (-b - sqrt(discriminant)) / (2.0 * a);
			}
			else
			{
				return -1;
			}
		}
		static bool isIntersect(const Ray & ray, const Sphere & sphere, float tmax, float tmin, IntersectPoint& intersectpoint)
		{
			Vector3 oc = ray.getPosition() - sphere.m_Center;
			float a = dot(ray.getDirction(), ray.getDirction());
			float b = 2 * dot(oc, ray.getDirction());
			float c = dot(oc, oc) - sphere.m_Radius * sphere.m_Radius;
			float discriminant = b * b - 4 * a *c;
			if (discriminant > 0)
			{
				float temp = (-b - sqrt(b *b - a *c)) / a;
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
}
#endif
