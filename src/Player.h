#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"
#include "OBJRenderer.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �v���C���[
class Player : public BaseGameObject
{
public:
	/// name �R���X�g���N�^
	//@{
	Player();
	//@}

	/// @name ������/�X�V/�`��
	//@{
	void initialize() override;
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �{�X�̈ʒu��ݒ肷��
	void setBossPos(const Vector3& aPos);
	//@}

private:
	/// @name ��������
	//@{
	void move();
	void shot();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	OBJRenderer mRenderer;
	Vector2 mVelocity;
	float mDistanceFromBoss;
	DirectX::XMMATRIX mPoseMat;
	//@}

	/// @name ���̃I�u�W�F�N�g�Ƃ̌q����
	//@{
	Vector3 mBossPos;
	//@}

};

} // namespace
// EOF
