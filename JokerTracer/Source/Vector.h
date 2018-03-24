#ifndef __MATH_VECTOR_H__
#define __MATH_VECTOR_H__
#include <math.h>
namespace Joker
{
	class Vector2;
	class Vector3;
	class Vector4;

	class Vector2
	{
	public:
		Vector2();

		Vector2(float xx, float yy);

	public:
		union
		{
			float data[2];
			struct
			{
				float x, y;
			};
		};
	};


	class Vector3
	{
	public:
		Vector3();

		Vector3(Vector2  pos, float zz);

		Vector3(float xx, float yy, float zz);

		Vector3(Vector4 inv);

		void normalize();

		Vector3 cross(const Vector3 &other);

		float legth();
	public:
		union
		{
			float data[3];
			struct
			{
				float x, y, z;
			};
		};
	};

	class Vector4
	{
	public:
		Vector4();

		Vector4(Vector3 pos, float ww);

		Vector4(float xx, float yy, float zz, float ww);

	public:
		union
		{
			float data[4];
			struct
			{
				float x, y, z, w;
			};
		};

	};

	Vector2 operator/(const Vector2& left, float f);
	Vector2 operator/(float f, const Vector2& left);
	Vector2 operator*(const Vector2& left, float f);
	Vector2 operator*(float f, const Vector2& left);
	Vector2 operator-(const Vector2& left, const Vector2& right);
	Vector2 operator+(const Vector2& left, const Vector2& right);

	Vector3 operator/(const Vector3& left, float f);
	Vector3 operator/(float f, const Vector3& left);
	Vector3 operator*(const Vector3& left, float f);
	Vector3 operator*(float f, const Vector3& left);
	Vector3 operator-(const Vector3& left, const Vector3& right);
	Vector3 operator+(const Vector3& left, const Vector3& right);
	Vector3 operator+(const Vector3& left, float f);

	Vector4 operator*(const Vector4& left, const Vector4& right);

	float dot(const Vector3& left, const Vector3& right);

	Vector3 cross(const Vector3& left, const Vector3& right);

	Vector3 normalize(Vector3& invector);


}

#endif