#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class GrazeEffect : public BaseGameObject
{
public:
	/// @name コンストラクタ
	//@{
	GrazeEffect(Vector3 aObstractPos, Vector3 aPlayerPos);
	~GrazeEffect();
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
	Vector3 mVelocity;
	//@}

};

} // namespace
// EOF
