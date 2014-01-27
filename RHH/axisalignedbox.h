#ifndef BOXAXISALIGNED_H
#define BOXAXISALIGNED_H

#include "collidable.h"

namespace Collision
{
	class AxisAlignedBox : public Collidable
	{
	private:
		friend Point;
		friend Circle;

		float min_x;
		float min_y;
		float max_x;
		float max_y;
	public:
		//Constructor / Destructor
		AxisAlignedBox(float position_x, float position_y, float size);
		AxisAlignedBox(float position_x, float position_y, float size_x, float size_y);
		~AxisAlignedBox(){}

		//Intersect
		bool Intersect(const Collidable& collidable)const;
		bool Intersect(const Point& point)const;
		bool Intersect(const Circle& circle)const;
		bool Intersect(const AxisAlignedBox& box)const;

		bool Contains(const AxisAlignedBox& box)const;

		//Accessors - Get
		float GetPositionX()const;
		float GetPositionY()const;
		float GetSizeX()const;
		float GetSizeY()const;

		//Accessors - Set
		void SetPositionX(float position_x);
		void SetPositionY(float position_y);
		void SetSizeX(float size_x);
		void SetSizeY(float size_y);

		void Move(float x, float y);
	};
}

#endif