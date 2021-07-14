#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "Player.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームカメラ
class GameCamera : public BaseCamera
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	GameCamera();
	~GameCamera();
	//@}

	/// @name 初期化/更新/描画
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	Player* mPlayer;
	float mKatamuki;
	//@}

};

} // namespace
// EOF
