#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "GameObjectTag.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 全てのゲームオブジェクトの基底クラス
class Camera : public BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	Camera();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}


protected:
	/// @name プロテクテッドメンバ関数
	//@{
	void setUpTransform();
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
