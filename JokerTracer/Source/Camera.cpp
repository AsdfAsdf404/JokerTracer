#include "Camera.h"
#include "Vector.h"
#include "Intersect.h"

Joker::Vector3 lensRandomInUnit()
{
	Joker::Vector3 p;
	do 
	{
		p = 2.0 * Joker::Vector3(Joker::drand48(), Joker::drand48(), 0) - Joker::Vector3(1,1,0);
	} while (dot(p, p) >= 1.0);


	return p;
}


Joker::Camera::Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist)
{
	lens_radius = aperture / 2;
	float theta = vfov * 3.141593 / 180.0f;
	float half_height = tan(theta * 0.5);
	float half_width = aspect * half_height;
	origin = lookfrom;
	w = lookfrom - lookat;
	w.normalize();
	u = cross(vup, w);
	u.normalize();
	v = cross(w, u);

	leftDown = origin - half_width * focus_dist * u - half_height* focus_dist * v - focus_dist * w;
	horizontal = 2 * half_width * focus_dist* u;
	vertical = 2 * half_height * focus_dist * v;
}

Joker::Ray Joker::Camera::getRay(float s, float t)
{
	Vector3 rd = lens_radius * lensRandomInUnit();
	Vector3 offset = rd.x * u  + v * rd.y;
	return Ray(origin + offset, leftDown + s * horizontal + t * vertical - origin - offset);
}
