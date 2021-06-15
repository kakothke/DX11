#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �e�X�g�p�̃Q�[���I�u�W�F�N�g
class TestObj : public BaseGameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	TestObj();
	TestObj(Transform aTransform);
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
	OBJRenderer mRenderer;
	//@}

};

} // namespace
// EOF
