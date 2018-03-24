#ifndef __MATERIAL_H__
#define __MATERIAL_H__
#include "Ray.h"
#include "Intersect.h"
#include "Vector.h"

namespace Joker
{
	class Material
	{
	public:
		virtual bool scanter(const Ray &ray, const hit_record & rec, Vector3 & attenuation, Ray &scatter ) const = 0;
	};

	class Lambertian : public Material
	{
	public:
		Lambertian(const Vector3 & a);

		virtual bool scanter(const Ray &ray, const hit_record & rec, Vector3 & attenuation, Ray &scatter)const;

		Vector3 albedo;
	};

	Vector3 reflect(const Vector3 & v, const Vector3 normal);

	class Metal : public Material
	{
	public:
		Metal(const Vector3 & a,  float  fuzz);

		virtual bool scanter(const Ray &ray, const hit_record & rec, Vector3 & attenuation, Ray &scatter)const;

		Vector3 albedo;
		float fuzz;
	};
}
#endif
