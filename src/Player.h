#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// プレイヤー
class Player : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	Player();
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
	//@}

};

} // namespace
// EOF
