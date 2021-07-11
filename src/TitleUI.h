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
	SpriteRenderer mArrowRenderer;
	SpriteRenderer mLogoRenderer;
	SpriteRenderer mStartRenderer;
	SpriteRenderer mBlackRenderer;
	Color mBlackColor;
	bool mStartButtonDown;
	//@}

};

} // namespace
// EOF
