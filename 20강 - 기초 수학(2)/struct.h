#pragma once

struct Vec2 // 크기와 방향을 의미하는 벡터.
{
	float x;
	float y;

public:
	float Length() // 벡터의 길이.(빗변의 길이)
	{
		return sqrt(x * x + y * y); // sqrt: 루트 함수.
	}

	Vec2& Normalize() // 벡터를 정규화(단위 벡터로 변환)하는 함수.
	{
		float fLen = Length();

		assert(fLen != 0.f); // 길이가 0 이면 예외처리.

		x /= fLen;
		y /= fLen;

		return *this;
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{
	}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{
	}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{
	}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{
	}
};