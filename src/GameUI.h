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
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	GameUI();
	~GameUI();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	void setScore(int aMeter);
	void setMissFlagTrue();
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
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
