#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"
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

	/// @ name 変換関数
	//@{
	/// オブジェクトの右方向のベクトルを返す
	Vector3 Right() const;
	/// オブジェクトの上方向のベクトルを返す
	Vector3 Up() const;
	/// オブジェクトの前方向のベクトルを返す
	Vector3 Forward() const;
	/// WorldMatrixに変換して返す
	DirectX::XMMATRIX WorldMatrix() const;
	//@}

	/// @name 演算子オーバーロード
	//@{
	void operator =(const Transform& aTransform);
	//@}

	/// @name メンバ変数
	//@{
	/// 位置
	Vector3 pos;
	/// 回転
	Quaternion rot;
	/// スケール
	Vector3 scale;
	/// 親からの位置
	Vector3 localPos;
	/// 親からの回転
	Quaternion localRot;
	/// 親からのスケール
	Vector3 localScale;
	//@}

};

} // namespace
// EOF
