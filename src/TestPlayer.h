#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "OBJRenderer.h"
#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ボス戦用テストプレイヤー
class TestPlayer : public BaseGameObject
{
public:
	/// name コンストラクタ/デストラクタ
	//@{
	TestPlayer();
	~TestPlayer();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name アクセサ
	//@{
	/// 移動速度を取得する
	const Vector2& moveVelocity();
	//@}

private:
	/// @name 内部実装
	//@{
	void move();
	void shot();
	//@}

	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	Vector3 mTargetPos;
	Vector2 mMoveVelocity;
	float mTargetDistance;
	float mRapidShotTimer;
	//@}

};

} // namespace
// EOF
