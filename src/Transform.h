#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// オブジェクトの位置、回転、スケールを扱うクラス
class Transform
{
public:
	/// @name コンストラクタ
	//@{
	Transform();
	Transform(Vector3 aPos, Vector3 aRot, Vector3 aScale);
	//@}

	//@ name 変換関数
	//@{
	/// XMFLOAT3X3型に変換して返す
	DirectX::XMFLOAT3X3 XMFLOAT3X3() const;
	//@}

	/// @name メンバ変数
	//@{
	/// 位置
	Vector3 pos;
	/// 回転
	Vector3 rot;
	/// スケール
	Vector3 scale;
	//@}

};

} // namespace
// EOF
