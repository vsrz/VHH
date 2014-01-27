#include "axisalignedbox.h"

#include "point.h"
#include "circle.h"

namespace Collision
{
	//Constructors/Destructors

	AxisAlignedBox::AxisAlignedBox(float position_x, float position_y, float size)
		: min_x(position_x-size/2), min_y(position_y-size/2), max_x(position_x+size/2), max_y(position_y+size/2)
	{}

	AxisAlignedBox::AxisAlignedBox(float position_x, float position_y, float size_x, float size_y)
		: min_x(position_x-size_x/2), min_y(position_y-size_y/2), max_x(position_x+size_x/2), max_y(position_y+size_y/2)
	{}

	//Intersect

	bool AxisAlignedBox::Intersect(const Collidable& collidable)const
	{ return collidable.Intersect(*this); }

	bool AxisAlignedBox::Intersect(const Point& point)const
	{
		if( min_x > point.position_x )
			return false;

		if( point.position_x > max_x )
			return false;

		if( min_y > point.position_y )
			return false;

		if( point.position_y > max_y )
			return false;

		return true;
	}

	bool AxisAlignedBox::Intersect(const Circle& circle)const
	{ return circle.Intersect(*this); }

	bool AxisAlignedBox::Intersect(const AxisAlignedBox& box)const
	{
		if( min_x > box.max_x )
			return false;

		if( box.min_x > max_x )
			return false;

		if( min_y > box.max_y )
			return false;

		if( box.min_y > max_y )
			return false;

		return true;
	}

	bool AxisAlignedBox::Contains(const AxisAlignedBox& box)const
	{
		if( min_x > box.min_x )
			return false;

		if( max_x < box.max_x )
			return false;

		if( min_y > box.min_y )
			return false;

		if( max_y < box.max_y )
			return false;

		return true;
	}

	//Accessors - Get
	float AxisAlignedBox::GetPositionX()const
	{ return (min_x + max_x)/2; }

	float AxisAlignedBox::GetPositionY()const
	{ return (min_y + max_y)/2; }

	float AxisAlignedBox::GetSizeX()const
	{ return max_x - min_x; }

	float AxisAlignedBox::GetSizeY()const
	{ return max_y - min_y; }

	//Accessorts - Set

	void AxisAlignedBox::SetPositionX(float position_x)
	{
		float offset = position_x - (min_x + max_x)/2;
		min_x += offset;
		max_x += offset;
	}

	void AxisAlignedBox::SetPositionY(float position_y)
	{
		float offset = position_y - (min_y + max_y)/2;
		min_y += offset;
		max_y += offset;
	}

	void AxisAlignedBox::SetSizeX(float size_x)
	{
		float offset = ( size_x - max_x + min_x )/2;
		min_x -= offset;
		max_x += offset;
	}

	void AxisAlignedBox::SetSizeY(float size_y)
	{
		float offset = ( size_y - max_y + min_y )/2;
		min_y -= offset;
		max_y += offset;
	}

	void AxisAlignedBox::Move(float x, float y)
	{
		min_x += x;
		max_x += x;

		min_y += y;
		max_y += y;
	}
}