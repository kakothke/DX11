#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �{�X��J����
class BossCamera : public Camera
{
public:
	/// @name �R���X�g���N�^
	//@{
	BossCamera();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �v���C���[�Ƃ̋���
	float mDistanceFromPlayer;
	//@}

};

} // namespace
// EOF
