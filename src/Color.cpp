#include "Color.h"

//-------------------------------------------------------------------------------------------------
#include "Math.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// 定数
const static float COLOR_MIN = 0.0f;
const static float COLOR_MAX = 1.0f;
const static float COLOR32 = 1.0f / 255.0f;

//-------------------------------------------------------------------------------------------------
/// static const メンバ変数
const Color Color::clear = Color(0.0f, 0.0f, 0.0f, 0.0f);
const Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);
const Color Color::magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
const Color Color::yellow = Color(1.0f, 0.92f, 0.016f, 1.0f);
const Color Color::gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color Color::grey = Color::gray;

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Color::Color()
	: r(COLOR_MAX)
	, g(COLOR_MAX)
	, b(COLOR_MAX)
	, a(COLOR_MAX)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param RGBA(0~1)
Color::Color(float rgba)
	: r(Math::Clamp(rgba, COLOR_MIN, COLOR_MAX))
	, g(Math::Clamp(rgba, COLOR_MIN, COLOR_MAX))
	, b(Math::Clamp(rgba, COLOR_MIN, COLOR_MAX))
	, a(Math::Clamp(rgba, COLOR_MIN, COLOR_MAX))
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param R(0~1)
/// @param G(0~1)
/// @param B(0~1)
/// @param A(0~1)
Color::Color(float r, float g, float b, float a)
	: r(Math::Clamp(r, COLOR_MIN, COLOR_MAX))
	, g(Math::Clamp(g, COLOR_MIN, COLOR_MAX))
	, b(Math::Clamp(b, COLOR_MIN, COLOR_MAX))
	, a(Math::Clamp(a, COLOR_MIN, COLOR_MAX))
{
}

//-------------------------------------------------------------------------------------------------
/// 0~255の間でColorを作成する
/// @param R(0~255) 
/// @param G(0~255) 
/// @param B(0~255) 
/// @param A(0~255) 
/// @return 0~255の間で作成され0~1の間に変換したColor
Color Color::Color32(int R, int G, int B, int A)
{
	Color out;
	out.r = (float)Math::Clamp(R, 0, 255) * COLOR32;
	out.g = (float)Math::Clamp(G, 0, 255) * COLOR32;
	out.b = (float)Math::Clamp(B, 0, 255) * COLOR32;
	out.a = (float)Math::Clamp(A, 0, 255) * COLOR32;
	return out;
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT4型に変換して返す
/// @return XMFLOAT4
DirectX::XMFLOAT4 Color::XMFLOAT4() const
{
	return {
		r,
		g,
		b,
		a
	};
}

//-------------------------------------------------------------------------------------------------
Color Color::operator +(float aValue) const
{
	return {
		Math::Clamp(r + aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g + aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b + aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a + aValue, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator -(float aValue) const
{
	return {
		Math::Clamp(r - aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g - aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b - aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a - aValue, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator *(float aValue) const
{
	return {
		Math::Clamp(r * aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g * aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b * aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a * aValue, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator /(float aValue) const
{
	return {
		Math::Clamp(r / aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g / aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b / aValue, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a / aValue, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator +(const Color& aColor) const
{
	return {
		Math::Clamp(r + aColor.r, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g + aColor.g, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b + aColor.b, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a + aColor.a, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator -(const Color& aColor) const
{
	return {
		Math::Clamp(r - aColor.r, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g - aColor.g, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b - aColor.b, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a - aColor.a, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator *(const Color& aColor) const
{
	return {
		Math::Clamp(r * aColor.r, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g * aColor.g, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b * aColor.b, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a * aColor.a, COLOR_MIN, COLOR_MAX)
	};
}
Color Color::operator /(const Color& aColor) const
{
	return {
		Math::Clamp(r / aColor.r, COLOR_MIN, COLOR_MAX),
		Math::Clamp(g / aColor.g, COLOR_MIN, COLOR_MAX),
		Math::Clamp(b / aColor.b, COLOR_MIN, COLOR_MAX),
		Math::Clamp(a / aColor.a, COLOR_MIN, COLOR_MAX)
	};
}

//-------------------------------------------------------------------------------------------------
bool Color::operator ==(const Color& aColor) const
{
	if (r != aColor.r || g != aColor.g || b != aColor.b || a != aColor.a) {
		return false;
	}
	return true;
}
bool Color::operator !=(const Color& aColor) const
{
	if (r == aColor.r && g == aColor.g && b == aColor.b && a == aColor.a) {
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
void Color::operator =(float aValue)
{
	aValue = Math::Clamp(aValue, COLOR_MIN, COLOR_MAX);
	r = aValue;
	g = aValue;
	b = aValue;
	a = aValue;
}
void Color::operator +=(float aValue)
{
	r = Math::Clamp(r + aValue, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g + aValue, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b + aValue, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a + aValue, COLOR_MIN, COLOR_MAX);
}
void Color::operator -=(float aValue)
{
	r = Math::Clamp(r - aValue, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g - aValue, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b - aValue, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a - aValue, COLOR_MIN, COLOR_MAX);
}
void Color::operator *=(float aValue)
{
	r = Math::Clamp(r * aValue, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g * aValue, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b * aValue, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a * aValue, COLOR_MIN, COLOR_MAX);
}
void Color::operator /=(float aValue)
{
	r = Math::Clamp(r / aValue, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g / aValue, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b / aValue, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a / aValue, COLOR_MIN, COLOR_MAX);
}
void Color::operator +=(const Color& aColor)
{
	r = Math::Clamp(r + aColor.r, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g + aColor.g, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b + aColor.b, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a + aColor.a, COLOR_MIN, COLOR_MAX);
}
void Color::operator -=(const Color& aColor)
{
	r = Math::Clamp(r - aColor.r, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g - aColor.g, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b - aColor.b, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a - aColor.a, COLOR_MIN, COLOR_MAX);
}
void Color::operator *=(const Color& aColor)
{
	r = Math::Clamp(r * aColor.r, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g * aColor.g, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b * aColor.b, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a * aColor.a, COLOR_MIN, COLOR_MAX);
}
void Color::operator /=(const Color& aColor)
{
	r = Math::Clamp(r / aColor.r, COLOR_MIN, COLOR_MAX);
	g = Math::Clamp(g / aColor.g, COLOR_MIN, COLOR_MAX);
	b = Math::Clamp(b / aColor.b, COLOR_MIN, COLOR_MAX);
	a = Math::Clamp(a / aColor.a, COLOR_MIN, COLOR_MAX);
}

} // namespace
// EOF
