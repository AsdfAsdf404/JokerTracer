#include "Intersect.h"
#include "Material.h"
#include "Sphere.h"

bool Joker::Intersect::isIntersect(const Ray & ray, const Sphere & sphere, float tmax, float tmin, hit_record& intersectpoint)
{
	Vector3 oc = ray.getPosition() - sphere.m_Center;

	float a = dot(ray.getDirction(), ray.getDirction());
	float b = dot(oc, ray.getDirction());
	float c = dot(oc, oc) - sphere.m_Radius * sphere.m_Radius;

	float discriminant = b * b - a *c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b *b - a *c)) / a;
		if (temp > tmin && temp < tmax)
		{
			intersectpoint.t = temp;
			intersectpoint.point = ray.getPoint(temp);
			intersectpoint.normal = (intersectpoint.point - sphere.m_Center) / sphere.m_Radius;
			intersectpoint.material = sphere.m_mat;
			return true;
		}

		temp = (-b + sqrt(b *b - a *c)) / a;
		if (temp > tmin && temp < tmax)
		{
			intersectpoint.t = temp;
			intersectpoint.point = ray.getPoint(temp);
			intersectpoint.normal = (intersectpoint.point - sphere.m_Center) / sphere.m_Radius;
			intersectpoint.material = sphere.m_mat;
			return true;
		}
	}

	return false;
}

Joker::hitable_list::hitable_list(std::vector<Sphere*> &list)
{
	m_list.assign(list.begin(), list.end());
}

Joker::hitable_list::hitable_list()
{

}

bool Joker::hitable_list::hit(const Ray & ray, float tmin, float tmax, hit_record& hit) const
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

#define m 0x100000000LL  
#define c 0xB16  
#define a 0x5DEECE66DLL  

static unsigned long long seed = 1;

double Joker::drand48(void)
{
	seed = (a * seed + c) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)m);
}

Joker::Vector3 Joker::randomInSphere()
{
	Vector3 p;
	float result;
	do
	{
		p = 2.0 * Vector3(drand48(), drand48(), drand48()) - Vector3(1, 1, 1);
		result = dot(p, p);
	} while (result >= 1.0);

	p.normalize();
	return p;
}
