#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �e�X�g�p�̃Q�[���I�u�W�F�N�g
class TestSprite : public BaseGameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	TestSprite();
	TestSprite(Transform aTransform);
	//@}

	/// @name ������/�X�V/�`��
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	SpriteRenderer mRenderer;
	//@}

};

} // namespace
// EOF
