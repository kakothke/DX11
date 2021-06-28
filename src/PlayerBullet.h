#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// プレイヤーの弾
class PlayerBullet : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	PlayerBullet(Transform aTransform, Vector3 aTargetPos);
	~PlayerBullet();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	OBJRenderer mRenderer;
	Vector3 mVelocity;
	float mTimer;
	//@}

};

} // namespace
// EOF
