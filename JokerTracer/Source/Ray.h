#ifndef __RAY_H__
#define __RAY_H__
#include "Vector.h"

namespace NMath
{
	class Ray
	{
	public:
		Ray()
		{

		}

		Ray(Vector3 pos, Vector3 dir):m_Position(pos), m_Dirction(dir)
		{

		}

		Vector3 getPoint(float t)
		{
			return (m_Position + m_Dirction * t);
		}

		Vector3 getDirction() const
		{
			return m_Dirction;
		}

		Vector3 getPosition() const
		{
			return m_Position;
		}

	private:
		Vector3 m_Position;
		Vector3 m_Dirction;
	};

}

#endif
