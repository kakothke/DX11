#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// カメラ基底クラス
/// @brief 静的なカメラとしても使用可能
class GameCamera : public Camera
{
public:
	/// @name コンストラクタ
	//@{
	GameCamera();
	GameCamera(Transform aTransform);
	GameCamera(Vector3 aCameraParam);
	GameCamera(Transform aTransform, Vector3 aCameraParam);
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:

};

} // namespace
// EOF
