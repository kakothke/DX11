#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class GameUI : public BaseGameObject
{
public:
	/// @name コンストラクタ/デストラクタ
	//@{
	GameUI();
	~GameUI();
	//@}

	/// @name 更新/描画
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	Transform mArrowTransform[4];
	SpriteRenderer mArrowRenderer[4];
	//@}

};

} // namespace
// EOF
