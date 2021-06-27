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
	/// �v���C���[�̃g�����X�t�H�[����ݒ肷��
	void setPlayerTransform(const Transform& aTransform);
	/// �v���C���[�̈ړ����x��ݒ肷��
	void setPlayerVelocity(const Vector2& aVelocity);
	//@}

private:
	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���[�J���g�����X�t�H�[��
	Transform mLocalTransform;
	/// �v���C���[�g�����X�t�H�[��
	Transform mPlayerTransform;
	/// �v���C���[�̈ړ����x
	Vector2 mPlayerVelocity;
	/// �v���C���[�Ƃ̋���
	float mDistanceFromPlayer;
	//@}

};

} // namespace
// EOF
