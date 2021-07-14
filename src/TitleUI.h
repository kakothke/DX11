#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class TitleUI : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	TitleUI();
	~TitleUI();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	SpriteRenderer mLogoRenderer;
	SpriteRenderer mStartRenderer;
	SpriteRenderer mStartArrowRenderer;
	SpriteRenderer mFadeRenderer;

	Transform mLogoTransform;
	Transform mArrowTransform;
	Transform mStartTransform;
	Transform mFadeTransform;

	Color mFadeColor;

	bool mStartButtonDown;
	//@}

};

} // namespace
// EOF
