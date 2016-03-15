#pragma once

struct Vec2
{
	short x, y;
	void operator+=(Vec2 & v){x += v.x; y += v.y;}
	void operator-=(Vec2 & v){x -= v.x; y -= v.y;}
	Vec2() : x(0), y(0) { }
	Vec2(int x, int y) : x(x), y(y) { }
	
};