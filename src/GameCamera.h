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
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name アクセサ
	//@{
	/// プレイヤーのトランスフォームを取得する
	void setPlayerTransform(const Transform& aTransform);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// ローカルトランスフォーム
	Transform mLocalTransform;
	/// プレイヤートランスフォーム
	Transform mPlayerTransform;
	/// プレイヤーとの距離
	float mDirectionFromPlayer;
	//@}

};

} // namespace
// EOF
