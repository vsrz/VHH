#include "circle.h"

#include "point.h"
#include "axisalignedbox.h"
#include <cmath>

static inline float Abs(float value)
{
	if(value < 0)
		return -value;
	return value;
}

static inline float clamp(float min, float max, float value)
{
	if(value < min)
		return min;
	else if(value > max)
		return max;
	return value;
}

namespace Collision
{
	//Constructor / Destructor

	Circle::Circle(float position_x, float position_y, float radius)
		: position_x(position_x), position_y(position_y), radius(radius)
	{}

	//Intersect

	bool Circle::Intersect(const Collidable& collidable)const
	{ return collidable.Intersect(*this); }

	bool Circle::Intersect(const Point& point)const
	{
		float distance_x = point.position_x - position_x;
		float distance_y = point.position_y - position_y;
		float distance_squared = distance_x * distance_x + distance_y * distance_y;

		if( distance_squared > radius * radius )
			return false;

		return true;
	}

	bool Circle::Intersect(const Circle& circle)const
	{
		float both_radius = radius + circle.radius;
		if( Abs(position_x - circle.position_x) > both_radius )
			return false;

		else if( Abs(position_y - circle.position_y) > both_radius )
			return false;

		float distance_x = position_x - circle.position_x;
		float distance_y = position_y - circle.position_y;
		float distance_squared = distance_x * distance_x + distance_y * distance_y;

		if( distance_squared > both_radius * both_radius )
			return false;

		return true;
	}

	bool Circle::Intersect(const AxisAlignedBox& box)const
	{
		if( box.min_x > position_x + radius )
			return false;

		else if( box.max_x < position_x - radius )
			return false;

		else if( box.min_y > position_y + radius )
			return false;

		else if( box.max_y < position_y - radius )
			return false;

		float closest_point_on_box_x = clamp(box.min_x, box.max_x, position_x);
		float closest_point_on_box_y = clamp(box.min_y, box.max_y, position_y);

		float distance_x = closest_point_on_box_x - position_x;
		float distance_y = closest_point_on_box_y - position_y;
		float distance_squared = distance_x * distance_x + distance_y * distance_y;

		if( distance_squared > radius * radius )
			return false;

		return true;
	}

	//Accessors - Get
	float Circle::GetPositionX()const
	{ return position_x; }

	float Circle::GetPositionY()const
	{ return position_y; }

	float Circle::GetRadius()const
	{ return radius; }

	//Accessors - Set
	void Circle::SetPositionX(float position_x)
	{ this->position_x = position_x; }

	void Circle::SetPositionY(float position_y)
	{ this->position_y = position_y; }

	void Circle::SetRadius(float radius)
	{ this->radius = radius; }

	void Circle::Move(float x, float y)
	{
		position_x += x;
		position_y += y;
	}
}
