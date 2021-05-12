#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "ObjRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// �e�X�g�p�̃Q�[���I�u�W�F�N�g
class Cube : public BaseGameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	Cube();
	Cube(Transform aTransform);
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
	ObjRenderer mRenderer;
	//@}

};

} // namespace
// EOF
