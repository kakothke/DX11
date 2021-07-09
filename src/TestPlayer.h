#pragma once

//-------------------------------------------------------------------------------------------------
#include <memory>
#include "BaseGameObject.h"
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
	/// ターゲットの位置を設定する
	void setTargetPos(const Vector3& aPos);
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
	std::list<std::shared_ptr<PlayerBullet>> mPlayerBullet;
	//@}

};

} // namespace
// EOF
