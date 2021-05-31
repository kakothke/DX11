#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// テスト用のゲームオブジェクト
class TestSprite : public BaseGameObject
{
public:
	/// name コンストラクタ
	//@{
	TestSprite();
	TestSprite(Transform aTransform);
	//@}

	/// @name 初期化/更新/描画
	//@{
	void initialize() override;
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
