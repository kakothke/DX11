#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// プレイヤーの弾
class PlayerBullet : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	PlayerBullet();
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
	SpriteRenderer mRenderer;
	//@}

};

} // namespace
// EOF
