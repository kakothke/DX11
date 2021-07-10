#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ゲームカメラ
class GameCamera : public Camera
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	GameCamera();
	~GameCamera();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	float mKatamuki;
	//@}

};

} // namespace
// EOF
