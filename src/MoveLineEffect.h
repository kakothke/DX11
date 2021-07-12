#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 移動線
class MoveLineEffect : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	MoveLineEffect();
	~MoveLineEffect();
	//@}

	/// @name 初期化/更新/描画
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

	/// @name アクセサ
	//@{
	void setMoveSpeed(const float aSpeed);
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	SpriteRenderer mRenderer;
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF
