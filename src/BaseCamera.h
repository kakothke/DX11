#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// カメラ基底クラス
/// @brief 静的なカメラとしても使用可能
class BaseCamera : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	BaseCamera();
	BaseCamera(Transform aTransform);
	BaseCamera(Vector3 aCameraParam);
	BaseCamera(Transform aTransform, Vector3 aCameraParam);
	virtual ~BaseCamera();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name コンスタントバッファを更新する
	//@{
	void updateConstantBuffer();
	//@}

protected:
	/// @name プロテクテッドメンバ変数
	//@{
	float mFov;
	float mNearZ;
	float mFarZ;
	//@}

};

} // namespace
// EOF
