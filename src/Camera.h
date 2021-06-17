#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// カメラ基底クラス
/// @brief 静的なカメラとしても使用可能
class Camera : public BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	Camera();
	Camera(Transform aTransform);
	Camera(Vector3 aCameraParam);
	Camera(Transform aTransform, Vector3 aCameraParam);
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	/// @name プロテクテッドメンバ関数
	//@{
	/// コンスタントバッファを更新する
	void updateConstantBuffer();
	//@}

	/// @name プロテクテッドメンバ変数
	//@{
	float mFov;
	float mNearZ;
	float mFarZ;
	//@}

};

} // namespace
// EOF
