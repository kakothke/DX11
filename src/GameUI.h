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

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	Transform mArrowTransform[4];
	SpriteRenderer mArrowRenderer[4];
	//@}

};

} // namespace
// EOF
