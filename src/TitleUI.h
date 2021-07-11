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
