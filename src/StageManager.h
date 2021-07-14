#pragma once

//-------------------------------------------------------------------------------------------------
#include "BaseGameObject.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �X�e�[�W�}�l�[�W���[
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
	void update();
	void draw();
	//@}

	/// @name �A�N�Z�T
	//@{
	/// ���[�g����Ԃ�
	int getScore();
	/// �~�X�t���O�𗧂Ă�
	void setMissFlagTrue();
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
	/// �~�X�C�x���g
	void missEvent();
	//@}

	/// @name �v���C�x�[�g�����o�ϐ�
	//@{
	/// ���x���A�b�v�^�C�}�[
	float mLevelUpTimer;
	/// ��Q�������^�C�}�[
	float mInstanceObstractTimer;
	/// �n�㐶���^�C�}�[
	float mInstanceGroundTimer;
	/// �ړ����G�t�F�N�g�����^�C�}�[
	float mInstanceMoveLineEffectTimer;
	/// �X�R�A
	float mScore;
	/// �X�s�[�h
	float mMoveSpeed;
	/// ���x��
	int mLevel;
	/// ��Q��������
	int mInstanceObstractCount;
	/// �~�X�t���O
	bool mMissFlag;
	//@}

};

} // namespace
// EOF
