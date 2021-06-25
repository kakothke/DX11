#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
	/// WorldMatrixに変換して返す
	DirectX::XMMATRIX worldMatrix() const;
	//@}

	/// @name メンバ変数
	//@{
	/// 位置
	Vector3 pos;
	/// 回転
	Quaternion rot;
	/// スケール
	Vector3 scale;
	//@}

};

} // namespace
// EOF
