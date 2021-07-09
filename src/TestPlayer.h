#pragma once

//-------------------------------------------------------------------------------------------------
#include <memory>
#include "BaseGameObject.h"
#include "OBJRenderer.h"
#include "PlayerBullet.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �{�X��p�e�X�g�v���C���[
class TestPlayer : public BaseGameObject
{
public:
	/// name �R���X�g���N�^/�f�X�g���N�^
	//@{
	TestPlayer();
	~TestPlayer();
	//@}

	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �A�N�Z�T
	//@{
	/// �ړ����x���擾����
	const Vector2& moveVelocity();
	/// �^�[�Q�b�g�̈ʒu��ݒ肷��
	void setTargetPos(const Vector3& aPos);
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
	Vector3 mTargetPos;
	Vector2 mMoveVelocity;
	float mTargetDistance;
	std::list<std::shared_ptr<PlayerBullet>> mPlayerBullet;
	//@}

};

} // namespace
// EOF
