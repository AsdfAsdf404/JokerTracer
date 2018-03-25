#pragma once
#include "Vector.h"
#include "Ray.h"

namespace Joker
{
	class Camera
	{
	public:
		Camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, float vfov, float aspect, float aperture, float focus_dist);

		Ray getRay(float u, float v);
	
		Vector3 origin;
		Vector3 leftDown;
		Vector3 horizontal;
		Vector3 vertical;
		Vector3 u, v, w;
		float lens_radius;
	};
}
