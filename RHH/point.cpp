#include "point.h"

#include "circle.h"
#include "axisalignedbox.h"
#include <cmath>

namespace Collision
{
	//Constructor / Destructor
	Point::Point(float position_x, float position_y, float position_z)
		: position_x(position_x), position_y(position_y), position_z(position_z)
	{}

	//Intersect
	bool Point::Intersect(const Collidable& collidable)const
	{ return collidable.Intersect(*this); }

	bool Point::Intersect(const Point& point)const
	{
		if(position_x != point.position_x)
			return false;

		if(position_y != point.position_y)
			return false;

		if(position_z != point.position_z)
			return false;

		return true;
	}

	bool Point::Intersect(const Circle& circle)const
	{ return circle.Intersect(*this); }

	bool Point::Intersect(const AxisAlignedBox& box)const
	{ return box.Intersect(*this); }

	//Accessors - Get
	float Point::GetPositionX()const
	{ return position_x; }

	float Point::GetPositionY()const
	{ return position_y; }

	float Point::GetPositionZ()const
	{ return position_z; }

	//Accerssors - Set
	void Point::SetPositionX(float position_x)
	{ this->position_x = position_x; }

	void Point::SetPositionY(float position_y)
	{ this->position_y = position_y; }

	void Point::SetPositionZ(float position_z)
	{ this->position_z = position_z; }
}