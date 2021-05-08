#pragma once
#include "Vector3Math.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// ベクトルの長さを返す
float Vector3Math::Magnitude(Vector3 aVector)
{
	return (float)sqrt(pow(aVector.x, 2.0) + pow(aVector.y, 2.0) + pow(aVector.z, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// 長さを1に変換したベクトルを返す
Vector3 Vector3Math::Normalized(Vector3 aVector)
{
	float magnitude = Magnitude(aVector);
	return {
		aVector.x / magnitude,
		aVector.y / magnitude,
		aVector.z / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT3型に変換して返す
const DirectX::XMFLOAT3& Vector3Math::XMFLOAT3(Vector3 aVector)
{
	return {
		aVector.x,
		aVector.y,
		aVector.z
	};
}

} // namespace
// EOF
