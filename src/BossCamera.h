#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseCamera.h"

//-------------------------------------------------------------------------------------------------
#include "TestPlayer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �{�X��J����
class BossCamera : public BaseCamera
{
public:
	/// @name �R���X�g���N�^
	//@{
	BossCamera();
	//@}

	/// @name ������/�X�V/�`��
	//@{
	void initialize();
	void update() override;
	void draw() override;
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// �v���C���[�I�u�W�F�N�g
	TestPlayer* mPlayer;
	/// �v���C���[�Ƃ̋���
	float mDistanceFromPlayer;
	//@}

};

} // namespace
// EOF
