#pragma once
#include "Vector2.h"
#include "moveCursor.h"

class Rect
{

	Vec2 min, max;

public:
	Rect(int minx, int miny, int maxx, int maxy)
		:min(minx,miny),max(maxx,maxy){}

	Vec2 getMin()
	{
		return min;
	}

	Vec2 getMax()
	{
		return max;
	}

	void setMin(Vec2 const & min)
	{
		this->min = min;
	}

	void setMax(Vec2 const & max)
	{
		this->max = max;
	}

	Rect(){}

	void draw(const char letter) const
	{
		for(int row = min.y; row < max.y; row++)
		{
			for(int col = min.x; col < max.x; col++)
			{
				if(row >= 0 && col >= 0)
				{
					moveCursor(col, row);
					putchar(letter);
				}
			}
		}
	}



	bool isOverlapping(Rect const & r) const
	{
		return !( min.x >= r.max.x || max.x <= r.min.x
		       || min.y >= r.max.y || max.y <= r.min.y);
	}

	void translate(Vec2 & delta)
	{
		min += delta;
		max += delta;
	}
};