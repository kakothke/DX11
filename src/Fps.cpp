#include "Fps.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Fps::Fps()
	: mFps(0)
	, mStartTime(0)
	, mCounter(0)
{
	timeBeginPeriod(1);
}

//-------------------------------------------------------------------------------------------------
/// �f�X�g���N�^
Fps::~Fps()
{
	timeEndPeriod(1);
}

//-------------------------------------------------------------------------------------------------
/// �X�V
void Fps::update()
{
	// 1�t���[���ڂȂ玞�����L��
	if (mCounter == 0) {
		mStartTime = timeGetTime();
	}
	// 60�t���[���ڂȂ畽�ς��v�Z����
	if (mCounter == Define::Fps) {
		int nowTime = timeGetTime();
		mFps = 1000.f / ((nowTime - mStartTime) / (float)Define::Fps);
		mCounter = 0;
		mStartTime = nowTime;
	}
	mCounter++;
}

//-------------------------------------------------------------------------------------------------
/// �҂�
void Fps::wait()
{
	// �����ɂ�����������
	int tookTime = timeGetTime() - mStartTime;
	// �҂���
	int waitTime = mCounter * 1000 / Define::Fps - tookTime;

	//�ҋ@
	if (waitTime > 0) {
		Sleep(waitTime);
	}
}

//-------------------------------------------------------------------------------------------------
/// ���݂�fps��`�悷��
void Fps::draw() const
{
	/*TCHAR debugText[20];
	_stprintf_s(debugText, 20, _T("%4.1ffps"), mFps);*/
}

} // namespace
// EOF
