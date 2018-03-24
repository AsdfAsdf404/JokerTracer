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
	
	bool refract(const Vector3 & v, const Vector3 &n, float ni_over_nt, Vector3 & result);

	float schlick(float cosine, float ref_idx);
	class Metal : public Material
	{
	public:
		Metal(const Vector3 & a,  float  fuzz);

		virtual bool scanter(const Ray &ray, const hit_record & rec, Vector3 & attenuation, Ray &scatter)const;

		Vector3 albedo;
		float fuzz;
	};


	class Dielectric : public Material
	{
	public:
		Dielectric(float ri);
		virtual bool scanter(const Ray &ray_in, const hit_record & rec, Vector3 & attenuation, Ray &scatter)const;

		float ref_idx;
	};
}
#endif
