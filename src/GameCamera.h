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
	/// プレイヤーのトランスフォームを設定する
	void setPlayerTransform(const Transform& aTransform);
	/// プレイヤーの移動速度を設定する
	void setPlayerVelocity(const Vector2& aVelocity);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// ローカルトランスフォーム
	Transform mLocalTransform;
	/// プレイヤートランスフォーム
	Transform mPlayerTransform;
	/// プレイヤーの移動速度
	Vector2 mPlayerVelocity;
	/// プレイヤーとの距離
	float mDistanceFromPlayer;
	//@}

};

} // namespace
// EOF
