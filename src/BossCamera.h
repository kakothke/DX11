#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "TestPlayer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ボス戦カメラ
class BossCamera : public BaseCamera
{
public:
	/// @name コンストラクタ
	//@{
	BossCamera();
	//@}

	/// @name 初期化/更新/描画
	//@{
	void initialize();
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// プレイヤーオブジェクト
	TestPlayer* mPlayer;
	/// プレイヤーとの距離
	float mDistanceFromPlayer;
	//@}

};

} // namespace
// EOF
