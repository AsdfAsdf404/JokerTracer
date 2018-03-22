#include "Window.h"
#include "Vector.h"
#include "Ray.h"
#include <iostream>
#include "Sphere.h"
#include "Intersect.h"

using namespace NMath;
const int WIDTH = 800;
const int HEIGHT = 600;

Vector3 getColor(const Ray &ray)
{
	Vector3 out;
	Sphere sphere(Vector3(0, 0, -1), 0.5);
	float res = Intersect::isIntersect(ray, sphere);

	if (res > 0)
	{
		Vector3 normal = (ray.getPoint(res) - Vector3(sphere.m_Center));
		normal.normalize();
		out = 0.5 * Vector3(normal.x + 1, normal.y + 1, normal.z + 1);
		return out;
	}

	Vector3 dir = ray.getDirction();
	dir.normalize();
	float t = 0.5 * (dir.y + 1.0);
	out = (1.0 - t)*Vector3(1.0, 1.0, 1.0) + t *Vector3(0.5, 0.7, 1.0);
	return out;
}

void setColor(int w, int h)
{
	Vector3 LeftDown(-4, -3, -1);
	Vector3 HDir(6, 0, 0);
	Vector3 WDir(0, 8, 0);
	Vector3 Origin(0, 0, 0);

	int * color = (int *)s_color;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			int pos = j * w + i;
			char * xp = (char*)(&color[pos]);

			float u = (float)i / (float)w;
			float v = (float)j / (float)h;
			Vector3 dir = LeftDown + u * WDir + v * HDir;
			Ray ray(Origin, dir);
			Vector3 c3 = getColor(ray);
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
