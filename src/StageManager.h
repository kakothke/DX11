#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

class StageManager : public BaseGameObject
{
public:
	/// @name �R���X�g���N�^/�f�X�g���N�^
	//@{
	StageManager();
	~StageManager();
	//@}
	
	/// @name �X�V/�`��
	//@{
	void update() override;
	void draw() override;
	//@}

private:
	/// @name ��������
	//@{
	/// ���x���X�V
	void updateLevel();
	/// �I�u�W�F�N�g�𐶐�����
	void instanceObj();
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
