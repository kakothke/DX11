#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "SpriteRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �ړ���
class MoveLineEffect : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	MoveLineEffect();
	~MoveLineEffect();
	//@}

	/// @name ������/�X�V/�`��
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	void setMoveSpeed(const float aSpeed);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	SpriteRenderer mRenderer;
	float mMoveSpeed;
	//@}

};

} // namespace
// EOF
