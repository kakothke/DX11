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

	/// @name アクセサ
	//@{
	void setScore(int aMeter);
	void setMissFlagTrue();
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	SpriteRenderer mArrowRenderer[4];
	SpriteRenderer mScoreRenderer[5];
	SpriteRenderer mRetryRenderer;
	SpriteRenderer mRetryArrowRenderer;
	SpriteRenderer mFadeRendererFront;
	SpriteRenderer mFadeRendererMiddle;
	SpriteRenderer mFadeRendererBack;

	Transform mArrowTransform[4];
	Transform mRetryTransform;
	Transform mRetryArrowTransform;
	Transform mFadeTransform;

	Color mFadeColorFront;
	Color mFadeColorMiddle;
	Color mFadeColorBack;

	float mScoreBlinkingTimer;
	int mScore;
	bool mMissFlag;
	bool mRetryFlag;
	//@}

};

} // namespace
// EOF
