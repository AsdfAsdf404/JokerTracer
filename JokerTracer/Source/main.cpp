#include "Window.h"
#include "Vector.h"
#include "Ray.h"
#include <iostream>
#include "Sphere.h"
#include "Intersect.h"
#include "Camera.h"
#include <stdlib.h>


using namespace NMath;
const int WIDTH = 800;
const int HEIGHT = 600;

#define m 0x100000000LL  
#define c 0xB16  
#define a 0x5DEECE66DLL  

static unsigned long long seed = 1;

double drand48(void)
{
	seed = (a * seed + c) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return  ((double)x / (double)m);
}

Vector3 randomInSphere()
{
	Vector3 p;
	float result;
	do 
	{
		p = 2.0 * Vector3(drand48(), drand48(), drand48()) - Vector3(1,1,1);
		result = dot(p, p);
	}
	while (result >= 1.0);

	return p;
}

Vector3 getColor(const Ray &ray, hitable_list& world)
{
	hit_record hit;
	if (world.hit(ray, 0,555555555, hit))
	{
		//return 0.5 * Vector3(hit.normal.x + 1, hit.normal.y + 1, hit.normal.z + 1);
		Vector3 target = hit.point + hit.normal + randomInSphere();
		return 0.5 * getColor(Ray(hit.point, target - hit.point), world);
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
	Camera cam;

	Sphere *s1 = new Sphere(Vector3(0, 0, -1), 0.5f);
	Sphere *s2 = new Sphere(Vector3(0, -100.5, -1), 100);

	std::vector<Sphere*> slist{ s1, s2 };
	hitable_list hitlist(slist);

	int samples = 1;

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

				c3 = c3 + getColor(ray, hitlist);
			}
				
			c3 = c3 / samples;

			int pos = j * width + i;
			char * xp = (char*)(&color[pos]);
			xp[0] = 255 * c3.z;
			xp[1] = 255 * c3.y;
			xp[2] = 255 * c3.x;
			xp[3] = 0;
		}
	}
	
}

int main(void)
{
	int indicator = 0;
	int kbhit = 0;
	float alpha = 1;
	float pos = 3.5;

	TCHAR *title = _T("Test - Test");

	if (screen_init(800, 600, title))return -1;

	setColor(WIDTH, HEIGHT);

	while (screen_exit == 0 && screen_keys[VK_ESCAPE] == 0)
	{
		screen_dispatch();

		if (screen_keys[VK_UP]) pos -= 0.01f;
		if (screen_keys[VK_DOWN]) pos += 0.01f;
		if (screen_keys[VK_LEFT]) alpha += 0.01f;
		if (screen_keys[VK_RIGHT]) alpha -= 0.01f;

		if (screen_keys[VK_SPACE])
		{
			if (kbhit == 0)
			{
				kbhit = 1;
				if (++indicator >= 3) indicator = 0;
				//device.render_state = states[indicator];
			}
		}
		else
		{
			kbhit = 0;
		}

		screen_update();
		Sleep(1);
	}
	return 0;
}
