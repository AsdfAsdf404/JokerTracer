#pragma once
#include "Vector.h"
#include "Ray.h"

namespace Joker
{
	class Camera
	{
	public:
		Camera()
		{
			origin = Vector3(0,0,0);
			leftDown = Vector3(-4, -3, -1);
			horizontal = Vector3(8.0, 0.0, 0.0);
			vertical = Vector3(0.0, 6.0, 0.0);
		}

		Ray getRay(float u, float v)
		{
			return Ray(origin, leftDown + u *horizontal + v * vertical - origin);
		}
	
		Vector3 origin;
		Vector3 leftDown;
		Vector3 horizontal;
		Vector3 vertical;
	};
}
