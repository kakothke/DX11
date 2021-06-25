#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// クォータニオン
class Quaternion
{
public:
	/// @name コンストラクタ
	//@{
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 aEulerAngle);
	Quaternion(Vector3 aAxis, float aAngle);
	//@}

	/// @name クォータニオン作成関数
	//@{
	/// Axisの周りをAngle度回転する回転を作成する
	static Quaternion AxisAngle(Vector3 aAxis, float aAngle);
	/// オイラー角で回転を作成する
	static Quaternion Euler(Vector3 aEulerAngle);
	//@}

	/// @name 変換関数
	//@{
	/// XMVECTORのメンバ変数を返す
	const DirectX::XMVECTOR& XMVECTOR() const;
	//@}

	/// @name 演算子オーバーロード
	//@{
	Quaternion operator -() const;
	DirectX::XMVECTOR operator *(const Quaternion& aQuaternion) const;

	bool operator ==(const Quaternion& aQuaternion) const;
	bool operator !=(const Quaternion& aQuaternion) const;

	void operator =(const DirectX::XMVECTOR& aQuaternion);
	void operator =(const Vector3& aEulerAngle);
	void operator *=(const Quaternion& aQuaternion);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	DirectX::XMVECTOR mQuaternion;
	//@}

};

} // namespace
// EOF
