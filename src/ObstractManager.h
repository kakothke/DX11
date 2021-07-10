#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class ObstractManager : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	ObstractManager();
	~ObstractManager();
	//@}
	
	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

	/// @name �����蔻��
	//@{
	bool collisionPlayer(const Vector3& aPos);
	//@}

private:
	/// @name ��������
	//@{
	/// ���x���X�V
	void updateLevel();
	/// �I�u�W�F�N�g�𐶐�����
	void instanceObj();
	/// ��Q���𐶐�����
	void instanceObstract();
	/// �n��𐶐�����
	void instanceGround();
	/// �X�s�[�h�ύX
	void changeSpeed();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���x���A�b�v�^�C�}�[
	float mLevelUpTimer;
	/// ��Q�������^�C�}�[
	float mInstanceObstractTimer;
	/// �n�㐶���^�C�}�[
	float mInstanceGroundTimer;
	/// �X�s�[�h
	float mMoveSpeed;
	/// ���x��
	int mLevel;
	/// ��Q��������
	int mInstanceObstractCount;
	//@}

};

} // namespace
// EOF
