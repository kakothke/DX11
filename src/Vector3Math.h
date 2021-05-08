#pragma once

//-------------------------------------------------------------------------------------------------
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ベクトル変換計算
class Vector3Math
{
public:
	//@ name 変換関数
	//@{
	/// ベクトルの長さを返す
	static float Magnitude(Vector3 aVector);
	/// 長さを1に変換したベクトルを返す
	static Vector3 Normalized(Vector3 aVector);
	/// XMFLOAT3型に変換して返す
	static const DirectX::XMFLOAT3& XMFLOAT3(Vector3 aVector);
	//@}

private:
	Vector3Math();

};

} // namespace
// EOF
