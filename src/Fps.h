#pragma once

//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <list>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// fps�𐧌䂷��
class Fps
{
public:
	/// @name �R���X�g���N�^
	//@{
	Fps();
	~Fps();
	//@}

	/// �X�V
	void update();
	/// �҂�
	void wait();
	/// ���݂�fps��`�悷��
	void draw() const;

private:
	/// name �v���C�x�[�g�����o�ϐ�
	//@{
	float mFps;
	int mStartTime;
	int mCounter;
	//@}

};

} // namespace
// EOF
