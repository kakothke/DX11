#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// ブースターエフェクト
class BoosterEffect : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	BoosterEffect(Transform aTransform);
	~BoosterEffect();
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
	Color mColor;
	//@}

};

} // namespace
// EOF
