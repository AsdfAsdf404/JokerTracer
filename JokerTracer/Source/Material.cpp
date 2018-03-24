#include "Material.h"



Joker::Lambertian::Lambertian(const Vector3 & a) : albedo(a)
{

}

bool Joker::Lambertian::scanter(const Ray &ray, const hit_record & rec, Vector3 & attenuation, Ray &scatter) const
{
	Vector3 target = rec.point + rec.normal + randomInSphere();
	scatter = Ray(rec.point, target - rec.point);
	attenuation = albedo;
	return true;
}

Joker::Vector3 Joker::reflect(const Vector3 & v, const Vector3 normal)
{
	return v - 2 * dot(v, normal) * normal;
}

Joker::Metal::Metal(const Vector3 & a, float f) :albedo(a), fuzz(f)
{

}

bool Joker::Metal::scanter(const Ray &ray, const hit_record & rec, Vector3 & attenuation, Ray &scatter) const
{
	Vector3 reflected = reflect(ray.getDirction(), rec.normal);
	reflected.normalize();
	scatter = Ray(rec.point, reflected + fuzz * randomInSphere());
	attenuation = albedo;
	return ((dot(scatter.getDirction(), rec.normal)) > 0);
}
