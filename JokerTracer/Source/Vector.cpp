#include "Vector.h"

Joker::Vector2::Vector2(float xx, float yy) :x(xx), y(yy)
{

}

Joker::Vector2::Vector2() : x(0), y(0)
{

}

Joker::Vector3::Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz)
{

}

Joker::Vector3::Vector3(Vector4 inv) : x(inv.x), y(inv.y), z(inv.z)
{

}

Joker::Vector3::Vector3(Vector2 pos, float zz) : x(pos.x), y(pos.y), z(zz)
{

}

Joker::Vector3::Vector3() : x(0), y(0), z(0)
{

}

void Joker::Vector3::normalize()
{
	float res = x * x + y * y + z * z;

	if (res != 0)
	{
		res = sqrt(res);
		x /= res;
		y /= res;
		z /= res;
	}
}

Joker::Vector3 Joker::Vector3::cross(const Vector3 &other)
{
	Vector3 res;
	res.x = y * other.z - z * other.y;
	res.y = z * other.x - x * other.z;
	res.z = x * other.y - y * other.x;
	return res;
}


Joker::Vector4::Vector4(Joker::Vector3 pos, float ww) :x(pos.x), y(pos.y), z(pos.z), w(ww)
{

}

Joker::Vector4::Vector4(float xx, float yy, float zz, float ww) : x(xx), y(yy), z(zz), w(ww)
{

}

Joker::Vector4::Vector4() : x(0), y(0), z(0), w(0)
{

}

Joker::Vector3 Joker::operator/(float f, const Vector3& left)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = f / left.data[i];
	}
	return res;
}

Joker::Vector3 Joker::operator/(const Vector3& left, float f)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = left.data[i] / f;
	}
	return res;
}

Joker::Vector3 Joker::operator*(const Vector3& left, float f)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = left.data[i] * f;
	}
	return res;
}

Joker::Vector2 Joker::operator/(float f, const Vector2& left)
{
	Vector2 res;
	for (int i = 0; i < 2; i++)
	{
		res.data[i] = f / left.data[i];
	}
	return res;
}

Joker::Vector2 Joker::operator/(const Vector2& left, float f)
{
	Vector2 res;
	for (int i = 0; i < 2; i++)
	{
		res.data[i] = left.data[i] / f;
	}
	return res;
}

Joker::Vector2 Joker::operator*(const Vector2& left, float f)
{
	Vector2 res;
	for (int i = 0; i < 2; i++)
	{
		res.data[i] = left.data[i] * f;
	}
	return res;
}

Joker::Vector2 Joker::operator*(float f, const Vector2& left)
{
	Vector2 res;
	for (int i = 0; i < 2; i++)
	{
		res.data[i] = left.data[i] * f;
	}
	return res;
}

Joker::Vector2 Joker::operator-(const Vector2& left, const Vector2& right)
{
	Vector2 res;
	for (int i = 0; i < 2; i++)
	{
		res.data[i] = left.data[i] - right.data[i];
	}
	return res;
}

Joker::Vector4 Joker::operator*(const Vector4& left, const Vector4& right)
{
	Joker::Vector4 res;
	for (int i = 0; i < 4; i++)
	{
		res.data[i] = left.data[i] * right.data[i];
	}
	return res;
}

Joker::Vector3 Joker::operator*(float f, const Vector3& left)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = left.data[i] * f;
	}
	return res;
}

Joker::Vector3 Joker::operator+(const Vector3& left, float f)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = left.data[i] + f;
	}
	return res;
}

Joker::Vector3 Joker::operator+(const Vector3& left, const Vector3& right)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = left.data[i] + right.data[i];
	}
	return res;
}

Joker::Vector3 Joker::operator-(const Vector3& left, const Vector3& right)
{
	Vector3 res;
	for (int i = 0; i < 3; i++)
	{
		res.data[i] = left.data[i] - right.data[i];
	}
	return res;
}

Joker::Vector2 Joker::operator+(const Vector2& left, const Vector2& right)
{
	Vector2 res;
	for (int i = 0; i < 2; i++)
	{
		res.data[i] = left.data[i] + right.data[i];
	}
	return res;
}

float Joker::dot(const Vector3& left, const Vector3& right)
{
	float res = 0;
	for (int i = 0; i < 3; i++)
	{
		res += left.data[i] * right.data[i];
	}
	return res;
}

Joker::Vector3 Joker::cross(const Vector3& left, const Vector3& right)
{
	Vector3 res;
	res.x = left.y * right.z - left.z * right.y;
	res.y = left.z * right.x - left.x * right.z;
	res.z = left.x * right.y - left.y * right.x;
	return res;
}

Joker::Vector3 Joker::normalize(Vector3& invector)
{
	Vector3 res;
	float doot = dot(invector, invector);
	doot = sqrt(doot);
	res = invector * (1 / doot);
	return res;
}