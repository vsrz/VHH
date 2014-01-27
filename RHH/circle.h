#ifndef SPHERE_H
#define SPHERE_H

#include "collidable.h"

namespace Collision
{
	class Circle : public Collidable
	{
	private:
		friend Point;
		friend AxisAlignedBox;

		float position_x;
		float position_y;
		float position_z;
		float radius;
	public:
		//Constructor / Destructor
		Circle(float position_x, float position_y, float radius);
		~Circle(){}

		//Intersect
		bool Intersect(const Collidable& collidable)const;
		bool Intersect(const Point& point)const;
		bool Intersect(const Circle& circle)const;
		bool Intersect(const AxisAlignedBox& box)const;

		//Accessors - Get
		float GetPositionX()const;
		float GetPositionY()const;
		float GetRadius()const;

		//Accessors - Set
		void SetPositionX(float position_x);
		void SetPositionY(float position_y);
		void SetRadius(float radius);

		void Move(float x, float y);
	};
}

#endif