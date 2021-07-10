#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ボス戦カメラ
class BossCamera : public Camera
{
public:
	/// @name コンストラクタ
	//@{
	BossCamera();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// プレイヤーとの距離
	float mDistanceFromPlayer;
	//@}

};

} // namespace
// EOF
