#pragma once

//-------------------------------------------------------------------------------------------------
#include "Camera.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �J�������N���X
/// @brief �ÓI�ȃJ�����Ƃ��Ă��g�p�\
class GameCamera : public Camera
{
public:
	/// @name �R���X�g���N�^
	//@{
	GameCamera();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �v���C���[�̃g�����X�t�H�[�����擾����
	void setPlayerTransform(const Transform& aTransform);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���[�J���g�����X�t�H�[��
	Transform mLocalTransform;
	/// �v���C���[�g�����X�t�H�[��
	Transform mPlayerTransform;
	/// �v���C���[�Ƃ̋���
	float mDirectionFromPlayer;
	//@}

};

} // namespace
// EOF
