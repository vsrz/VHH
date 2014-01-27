#ifndef COLLIDABLE_H
#define COLLIDABLE_H

namespace Collision
{
	class Point;
	class Circle;
	class AxisAlignedBox;

	class Collidable
	{
	public:
		virtual ~Collidable(){};
		virtual bool Intersect(const Collidable& collidable)const=0;
		virtual bool Intersect(const Point& point)const=0;
		virtual bool Intersect(const Circle& circle)const=0;
		virtual bool Intersect(const AxisAlignedBox& box)const=0;
	};
}

#endif