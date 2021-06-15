#include "Fps.h"

//-------------------------------------------------------------------------------------------------
#include "Define.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Fps::Fps()
	: mFps(0)
	, mStartTime(0)
	, mCounter(0)
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
	// 60フレーム目なら平均を計算する
	if (mCounter == Define::Fps) {
		int nowTime = timeGetTime();
		mFps = 1000.f / ((nowTime - mStartTime) / (float)Define::Fps);
		mCounter = 0;
		mStartTime = nowTime;
	}
	mCounter++;
}

//-------------------------------------------------------------------------------------------------
/// 待つ
void Fps::wait()
{
	// 処理にかかった時間
	int tookTime = timeGetTime() - mStartTime;
	// 待つ時間
	int waitTime = mCounter * 1000 / Define::Fps - tookTime;

	//待機
	if (waitTime > 0) {
		Sleep(waitTime);
	}
}

//-------------------------------------------------------------------------------------------------
/// 現在のfpsを描画する
void Fps::draw() const
{
	/*TCHAR debugText[20];
	_stprintf_s(debugText, 20, _T("%4.1ffps"), mFps);*/
}

} // namespace
// EOF
