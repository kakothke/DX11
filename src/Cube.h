#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// ������
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
	OBJRenderer mRenderer;
	//@}

};

} // namespace
// EOF
