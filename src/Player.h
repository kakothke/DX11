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
	/// ボスの位置を設定する
	void setBossPos(const Vector3& aPos);
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
	float mTargetDistance;
	float mMoveVelocity;
	//@}

};

} // namespace
// EOF
