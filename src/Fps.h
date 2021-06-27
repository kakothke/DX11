#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include "Singleton.h"

#pragma comment(lib,"winmm.lib")

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// fps�𐧌䂷��
class Fps : public Singleton<Fps>
{
public:
	/// @name �R���X�g���N�^
	//@{
	Fps();
	~Fps();
	//@}

	/// @name �X�V
	//@{
	void update();
	//@}

	/// @name �O�t���[�����炩���������Ԃ�Ԃ�
	//@{
	float deltaTime();
	//@}

	/// @name �A�N�Z�T
	//@{
	/// ���݂�fps�l��Ԃ�
	const float& fps();
	/// fps�̕��ς����T���v������ݒ肷��
	void setFpsCount(int aFpsCount);
	//@}

private:
	/// name �v���C�x�[�g�����o�ϐ�
	//@{
	/// fps
	float mFps;
	/// ���ς����T���v����
	int mFpsCount;
	/// ����J�n����
	int mStartTime;
	/// �J�E���^
	int mCounter;
	/// �����ҋ@����
	int mWaitTime;
	//@}

};

} // namespace
// EOF
