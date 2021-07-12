#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 爆発エフェクト
class ExplosionEffect : public BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	ExplosionEffect(Vector3 aInstancePos);
	~ExplosionEffect();
	//@}

	/// @name 初期化/更新/描画
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
