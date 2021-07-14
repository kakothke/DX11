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
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	TitleUI();
	~TitleUI();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
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
