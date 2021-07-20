#include "Fps.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param aFpsCount 平均を取るサンプル数
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
/// デストラクタ
Fps::~Fps()
{
	timeEndPeriod(1);
}

//-------------------------------------------------------------------------------------------------
/// 更新
void Fps::update()
{
	// 1フレーム目なら時刻を記憶
	if (mCounter == 0) {
		mStartTime = timeGetTime();
	}

	// 平均を計算する
	if (mCounter == mFpsCount) {
		int nowTime = timeGetTime();
		mFps = 1000.f / ((nowTime - mStartTime) / (float)mFpsCount);
		mCounter = 0;
		mStartTime = nowTime;
	}
	mCounter++;

	// 待機
	int tookTime = timeGetTime() - mStartTime;
	mWaitTime = mCounter * 1000 / mFpsCount - tookTime;
	if (mWaitTime > 0) {
		Sleep(mWaitTime);
	}
}

//-------------------------------------------------------------------------------------------------
/// 前フレームからかかった時間を返す
/// @return 前フレームからかかった時間
float Fps::deltaTime()
{
	float out = mWaitTime / 1000.0f;
	if (out < 0.0f) {
		return 0.001f;
	}
	return out;
}

//-------------------------------------------------------------------------------------------------
/// 現在のfps値を返す
/// @return 現在のfps値
const float& Fps::fps()
{
	return mFps;
}

//-------------------------------------------------------------------------------------------------
/// fpsの平均を取るサンプル数を設定する
/// @param aFpsCount サンプル数
void Fps::setFpsCount(int aFpsCount)
{
	mFpsCount = aFpsCount;
}

} // namespace
// EOF
