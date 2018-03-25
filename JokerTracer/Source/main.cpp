#include "Window.h"
#include "Vector.h"
#include "Ray.h"
#include <iostream>
#include "Sphere.h"
#include "Intersect.h"
#include "Camera.h"
#include <stdlib.h>
#include "Material.h"

using namespace Joker;
const int WIDTH = 800;
const int HEIGHT = 600;



Vector3 getColor(const Ray &ray, hitable_list& world, int depth)
{
	hit_record hit;
	if (world.hit(ray, 0,555555, hit))
	{
		//return 0.5 * Vector3(hit.normal.x + 1, hit.normal.y + 1, hit.normal.z + 1);

		//Vector3 target = hit.point + hit.normal + randomInSphere();
		//return 0.5 * getColor(Ray(hit.point, target - hit.point), world);

		Ray scater;
		Vector3 attenuation;
		if (depth < 50 && hit.material->scanter(ray, hit, attenuation, scater))
		{
			Vector3 co = getColor(scater, world, depth + 1);
			co = Vector3(co.x * attenuation.x, co.y * attenuation.y, co.z * attenuation.z);
			return co;
		} 
		else
		{
			return Vector3(0, 0, 0);
		}
	}
	else
	{
		Vector3 dir = ray.getDirction();
		dir.normalize();

		float t = 0.5 * ( dir.y + 1.0);
		return (1 - t)*Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5,0.7,1.0);
	}

}

void setColor(int width, int height)
{
	Vector3 from = Vector3(-2, 2, 1);
	Vector3 at = Vector3(0, 0, -1);
	float dis_to_focus = (from - at).legth();
	float aperture = 0.2;
	Camera cam(from, at, Vector3(0,1,0), 60, (float) width/ (float)height, aperture, dis_to_focus);

	Sphere *s1 = new Sphere(Vector3(0, 0, -1), 0.5f, new Lambertian(Vector3(0.8,0.3,0.3)));
	Sphere *s2 = new Sphere(Vector3(0, -100.5, -1), 100, new Lambertian(Vector3(0.8,0.8,0.0)));
	Sphere *s3 = new Sphere(Vector3(1, 0, -1), 0.5, new Metal(Vector3(0.8, 0.6, 0.2), 1.0));
	Sphere *s4 = new Sphere(Vector3(-1, 0, -1), 0.5, new Dielectric(1.5));
	Sphere *s5 = new Sphere(Vector3(-1, 0, -1), -0.45, new Dielectric(1.5));

	std::vector<Sphere*> slist{ s1, s2, s3, s4 };
	hitable_list hitlist(slist);

	int samples = 20;

	int * color = (int *)s_color;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			Vector3 c3;

			for (int k = 0; k < samples; k++)
			{
				float u = (float)(i + drand48()) / (float)width;
				float v = (float)(j + drand48()) / (float)height;

				Ray ray = cam.getRay(u, v);

				c3 = c3 + getColor(ray, hitlist, 0);
			}
				
			c3 = c3 / samples;
			
			int pos = j * width + i;
			char * xp = (char*)(&color[pos]);
			xp[0] = 255 * sqrt(c3.z);
			xp[1] = 255 * sqrt(c3.y);
			xp[2] = 255 * sqrt(c3.x);
			xp[3] = 0;
		}
	}
	
}

int main(void)
{
	TCHAR *title = _T("Test - Test");

	if (screen_init(800, 600, title))return -1;

	setColor(WIDTH, HEIGHT);

	while (screen_exit == 0 && screen_keys[VK_ESCAPE] == 0)
	{
		screen_dispatch();

		screen_update();
		Sleep(1);
	}
	return 0;
}
