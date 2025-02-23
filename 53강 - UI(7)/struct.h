#pragma once

struct Vec2 // 크기와 방향을 의미하는 벡터.
{
	float x;
	float y;

public:
	bool IsZero() // 벡터가 0 인지 확인하는 함수.
	{
		if (x == 0.f && y == 0.f)
			return true;
		return false;
	}

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
	Vec2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}

	void operator += (Vec2 _vOther)
	{
		x += _vOther.x;
		y += _vOther.y;
	}

	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}

	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}

	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}

	Vec2 operator / (float _f)
	{
		assert( !(0.f == _f) );
		return Vec2(x / _f, y / _f);
	}

public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

	Vec2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}
};