#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param aFpsCount ���ς����T���v����
Fps::Fps()
	: mFps(0.0f)
	, mFpsCount()
	, mStartTime(0)
	, mCounter(0)
	, mWaitTime(0)
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

	// ���ς��v�Z����
	if (mCounter == mFpsCount) {
		int nowTime = timeGetTime();
		mFps = 1000.f / ((nowTime - mStartTime) / (float)mFpsCount);
		mCounter = 0;
		mStartTime = nowTime;
	}
	mCounter++;

	// �ҋ@
	int tookTime = timeGetTime() - mStartTime;
	mWaitTime = mCounter * 1000 / mFpsCount - tookTime;
	if (mWaitTime > 0) {
		Sleep(mWaitTime);
	}
}

//-------------------------------------------------------------------------------------------------
/// �O�t���[�����炩���������Ԃ�Ԃ�
/// @return �O�t���[�����炩����������
float Fps::deltaTime()
{
	float out = mWaitTime / 1000.0f;
	if (out < 0.0f) {
		return 0.001f;
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// ���݂�fps�l��Ԃ�
/// @return ���݂�fps�l
const float& Fps::fps()
{
	return mFps;
}

//-------------------------------------------------------------------------------------------------
/// fps�̕��ς����T���v������ݒ肷��
/// @param aFpsCount �T���v����
void Fps::setFpsCount(int aFpsCount)
{
	mFpsCount = aFpsCount;
}

} // namespace
// EOF
