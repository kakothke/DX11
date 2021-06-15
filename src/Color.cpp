#include "Color.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static int MIN = 0;
const static int MAX = 255;
const static float CONV = 1.0f / 255.0f;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Color::Color()
	: r(MAX)
	, g(MAX)
	, b(MAX)
	, a(MAX)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param RGBA(0~255)
Color::Color(int rgba)
	: r(Math::Clamp(rgba, MIN, MAX))
	, g(Math::Clamp(rgba, MIN, MAX))
	, b(Math::Clamp(rgba, MIN, MAX))
	, a(Math::Clamp(rgba, MIN, MAX))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param R(0~255)
/// @param G(0~255)
/// @param B(0~255)
/// @param A(0~255)
Color::Color(int r, int g, int b, int a)
	: r(Math::Clamp(r, MIN, MAX))
	, g(Math::Clamp(g, MIN, MAX))
	, b(Math::Clamp(b, MIN, MAX))
	, a(Math::Clamp(a, MIN, MAX))
{
}

//-------------------------------------------------------------------------------------------------
DirectX::XMFLOAT4 Color::XMFLOAT4() const
{
	return {
		r * CONV,
		g * CONV,
		b * CONV,
		a * CONV
	};
}

//-------------------------------------------------------------------------------------------------
Color Color::operator +(int aValue) const
{
	return {
		Math::Clamp(r + aValue, MIN, MAX),
		Math::Clamp(g + aValue, MIN, MAX),
		Math::Clamp(b + aValue, MIN, MAX),
		Math::Clamp(a + aValue, MIN, MAX)
	};
}
Color Color::operator -(int aValue) const
{
	return {
		Math::Clamp(r - aValue, MIN, MAX),
		Math::Clamp(g - aValue, MIN, MAX),
		Math::Clamp(b - aValue, MIN, MAX),
		Math::Clamp(a - aValue, MIN, MAX)
	};
}
Color Color::operator *(int aValue) const
{
	return {
		Math::Clamp(r * aValue, MIN, MAX),
		Math::Clamp(g * aValue, MIN, MAX),
		Math::Clamp(b * aValue, MIN, MAX),
		Math::Clamp(a * aValue, MIN, MAX)
	};
}
Color Color::operator /(int aValue) const
{
	return {
		Math::Clamp(r / aValue, MIN, MAX),
		Math::Clamp(g / aValue, MIN, MAX),
		Math::Clamp(b / aValue, MIN, MAX),
		Math::Clamp(a / aValue, MIN, MAX)
	};
}
Color Color::operator +(const Color& aColor) const
{
	return {
		Math::Clamp(r + aColor.r, MIN, MAX),
		Math::Clamp(g + aColor.g, MIN, MAX),
		Math::Clamp(b + aColor.b, MIN, MAX),
		Math::Clamp(a + aColor.a, MIN, MAX)
	};
}
Color Color::operator -(const Color& aColor) const
{
	return {
		Math::Clamp(r - aColor.r, MIN, MAX),
		Math::Clamp(g - aColor.g, MIN, MAX),
		Math::Clamp(b - aColor.b, MIN, MAX),
		Math::Clamp(a - aColor.a, MIN, MAX)
	};
}
Color Color::operator *(const Color& aColor) const
{
	return {
		Math::Clamp(r * aColor.r, MIN, MAX),
		Math::Clamp(g * aColor.g, MIN, MAX),
		Math::Clamp(b * aColor.b, MIN, MAX),
		Math::Clamp(a * aColor.a, MIN, MAX)
	};
}
Color Color::operator /(const Color& aColor) const
{
	return {
		Math::Clamp(r / aColor.r, MIN, MAX),
		Math::Clamp(g / aColor.g, MIN, MAX),
		Math::Clamp(b / aColor.b, MIN, MAX),
		Math::Clamp(a / aColor.a, MIN, MAX)
	};
}

//-------------------------------------------------------------------------------------------------
bool Color::operator ==(const Color& aColor) const
{
	if (r != aColor.r) {
		return false;
	}
	if (g != aColor.g) {
		return false;
	}
	if (b != aColor.b) {
		return false;
	}
	if (a != aColor.a) {
		return false;
	}
	return true;
}
bool Color::operator !=(const Color& aColor) const
{
	if (r == aColor.r) {
		return false;
	}
	if (g == aColor.g) {
		return false;
	}
	if (b == aColor.b) {
		return false;
	}
	if (a == aColor.a) {
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
void Color::operator =(int aValue)
{
	aValue = Math::Clamp(aValue, MIN, MAX);
	r = aValue;
	g = aValue;
	b = aValue;
	a = aValue;
}
void Color::operator +=(int aValue)
{
	r = Math::Clamp(r + aValue, MIN, MAX);
	g = Math::Clamp(g + aValue, MIN, MAX);
	b = Math::Clamp(b + aValue, MIN, MAX);
	a = Math::Clamp(a + aValue, MIN, MAX);
}
void Color::operator -=(int aValue)
{
	r = Math::Clamp(r - aValue, MIN, MAX);
	g = Math::Clamp(g - aValue, MIN, MAX);
	b = Math::Clamp(b - aValue, MIN, MAX);
	a = Math::Clamp(a - aValue, MIN, MAX);
}
void Color::operator *=(int aValue)
{
	r = Math::Clamp(r * aValue, MIN, MAX);
	g = Math::Clamp(g * aValue, MIN, MAX);
	b = Math::Clamp(b * aValue, MIN, MAX);
	a = Math::Clamp(a * aValue, MIN, MAX);
}
void Color::operator /=(int aValue)
{
	r = Math::Clamp(r / aValue, MIN, MAX);
	g = Math::Clamp(g / aValue, MIN, MAX);
	b = Math::Clamp(b / aValue, MIN, MAX);
	a = Math::Clamp(a / aValue, MIN, MAX);
}
void Color::operator +=(const Color& aColor)
{
	r = Math::Clamp(r + aColor.r, MIN, MAX);
	g = Math::Clamp(g + aColor.g, MIN, MAX);
	b = Math::Clamp(b + aColor.b, MIN, MAX);
	a = Math::Clamp(a + aColor.a, MIN, MAX);
}
void Color::operator -=(const Color& aColor)
{
	r = Math::Clamp(r - aColor.r, MIN, MAX);
	g = Math::Clamp(g - aColor.g, MIN, MAX);
	b = Math::Clamp(b - aColor.b, MIN, MAX);
	a = Math::Clamp(a - aColor.a, MIN, MAX);
}
void Color::operator *=(const Color& aColor)
{
	r = Math::Clamp(r * aColor.r, MIN, MAX);
	g = Math::Clamp(g * aColor.g, MIN, MAX);
	b = Math::Clamp(b * aColor.b, MIN, MAX);
	a = Math::Clamp(a * aColor.a, MIN, MAX);
}
void Color::operator /=(const Color& aColor)
{
	r = Math::Clamp(r / aColor.r, MIN, MAX);
	g = Math::Clamp(g / aColor.g, MIN, MAX);
	b = Math::Clamp(b / aColor.b, MIN, MAX);
	a = Math::Clamp(a / aColor.a, MIN, MAX);
}

} // namespace
// EOF
