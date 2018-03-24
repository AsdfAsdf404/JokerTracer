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

bool Joker::refract(const Vector3 & v, const Vector3 &n, float ni_over_nt, Vector3 & result)
{
	Vector3 uv = v;
	uv.normalize();

	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt *(1 - dt * dt);
	if (discriminant > 0)
	{
		result = ni_over_nt *(v - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
	return false;
}

float Joker::schlick(float cosine, float ref_idx)
{
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
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

Joker::Dielectric::Dielectric(float ri) :ref_idx(ri)
{

}

bool Joker::Dielectric::scanter(const Ray &ray_in, const hit_record & rec, Vector3 & attenuation, Ray &scatter) const
{
	Vector3 outward_normal;
	Vector3 reflected = reflect(ray_in.getDirction(), rec.normal);
	float ni_over_nt;
	attenuation = Vector3(1.0, 1.0, 1.0);
	Vector3 refracted;
	float reflect_prob;
	float consine;
	if (dot(ray_in.getDirction(), rec.normal) > 0)
	{
		outward_normal = -1 * rec.normal;
		ni_over_nt = ref_idx;
		consine = ref_idx * dot(ray_in.getDirction(), rec.normal) / ray_in.getDirction().legth();
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / ref_idx;
		consine = -1 * dot(ray_in.getDirction(), rec.normal) / ray_in.getDirction().legth();
	}

	if (refract(ray_in.getDirction(), outward_normal, ni_over_nt, refracted))
	{
		reflect_prob = schlick(consine, ref_idx);
	}
	else
	{
		scatter = Ray(rec.point, reflected);
		reflect_prob = 1.0;
	}

	if (drand48() < reflect_prob)
	{
		scatter = Ray(rec.point, reflected);
	}
	else
	{
		scatter = Ray(rec.point, refracted);
	}
	return true;
}
