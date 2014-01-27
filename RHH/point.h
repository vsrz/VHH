#ifndef POINT_H
#define POINT_H

#include "collidable.h"

namespace Collision
{
	class Point : public Collidable
	{
	private:
		friend Circle;
		friend AxisAlignedBox;

		float position_x;
		float position_y;
		float position_z;
	public:
		//Constructor / Destructor
		Point(float position_x, float position_y, float position_z);
		~Point(){}

		//Intersect
		bool Intersect(const Collidable& collidable)const;
		bool Intersect(const Point& point)const;
		bool Intersect(const Circle& circle)const;
		bool Intersect(const AxisAlignedBox& box)const;

		//Accessors - Get
		float GetPositionX()const;
		float GetPositionY()const;
		float GetPositionZ()const;

		//Accerssors - Set
		void SetPositionX(float position_x);
		void SetPositionY(float position_y);
		void SetPositionZ(float position_z);
	};
}

#endif